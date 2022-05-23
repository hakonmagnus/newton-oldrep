// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#include "newton/newton.h"
using namespace newton;

#include <iostream>

NtServer::NtServer()
    : m_connected{ false }
{
}

NtServer::~NtServer()
{
}

bool NtServer::sendData(NtContext* ctxPtr, const char* buf, size_t len)
{
    std::lock_guard<std::mutex> lock(ctxPtr->ctxLock);
    char* dataPositionPtr = const_cast<char*>(buf);
    size_t totalSent = 0;

    if (ctxPtr->isSentPending) {
        NtPendingSent pendingSent;
        pendingSent.pendingSentData = new char[len];
        pendingSent.pendingSentLen = len;
        memcpy(pendingSent.pendingSentData, buf, len);

        if (m_sockUsage == NT_USAGE_UDP_SERVER) {
            memcpy(&pendingSent.udpRemoteAddr, &ctxPtr->udpRemoteAddr, sizeof(pendingSent.udpRemoteAddr));
        }

        ctxPtr->pendingSendDeque.push_back(pendingSent);

#ifdef NT_APPLE
        if (!controlKq(ctxPtr, EVFILT_WRITE, EV_ADD | EV_ENABLE)) {
#else
        if (!controlEpoll(ctxPtr, EPOLLIN | EPOLLOUT | EPOLLERR | EPOLLRDHUP, EPOLL_CTL_MOD)) {
#endif
            delete[] pendingSent.pendingSentData;
            ctxPtr->pendingSendDeque.pop_back();
            return false;
        }
        return true;
    }

    while (totalSent < len) {
        int sentLen = 0;

        if (m_sockUsage == NT_USAGE_UDP_SERVER) {
            sentLen = sendto(ctxPtr->socket, dataPositionPtr, len - totalSent, 0,
                    (struct sockaddr*)&ctxPtr->udpRemoteAddr,
                    sizeof(ctxPtr->udpRemoteAddr));
        } else {
            sentLen = send(ctxPtr->socket, dataPositionPtr, len - totalSent, 0);
        }

        if (sentLen > 0) {
            totalSent += sentLen;
            dataPositionPtr += sentLen;
        } else if (sentLen < 0) {
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                NtPendingSent pendingSent;
                pendingSent.pendingSentData = new char[len - totalSent];
                pendingSent.pendingSentLen = len - totalSent;
                memcpy(pendingSent.pendingSentData, dataPositionPtr, len - totalSent);

                if (m_sockUsage == NT_USAGE_UDP_SERVER) {
                    memcpy(&pendingSent.udpRemoteAddr,
                            &ctxPtr->udpRemoteAddr, sizeof(pendingSent.udpRemoteAddr));
                }
                ctxPtr->pendingSendDeque.push_back(pendingSent);

#ifdef NT_APPLE
                if (!controlKq(ctxPtr, EVFILT_WRITE, EV_ADD | EV_ENABLE) {
#else
                if (!controlEpoll(ctxPtr, EPOLLIN | EPOLLOUT | EPOLLERR | EPOLLRDHUP, EPOLL_CTL_MOD)) {
#endif
                    delete[] pendingSent.pendingSentData;
                    ctxPtr->pendingSendDeque.pop_back();
                    return false;
                }

                ctxPtr->isSentPending = true;
                return true;
            } else if (errno != EINTR) {
                std::lock_guard<std::mutex> lock(m_errMsgLock);
                m_errMsg = "send error: " + std::string(strerror(errno));
                return false;
            }
        }
    }

    return true;
}

bool NtServer::setSocketNonBlocking(int fd)
{
    int oldflags;

    if ((oldflags = fcntl(fd, F_GETFL, 0)) < 0) {
        std::lock_guard<std::mutex> lock(m_errMsgLock);
        m_errMsg = "fcntl F_GETFL error: " + std::string(strerror(errno));
        return false;
    }

    int ret = fcntl(fd, F_SETFL, oldflags | O_NONBLOCK);

    if (ret < 0) {
        std::lock_guard<std::mutex> lock(m_errMsgLock);
        m_errMsg = "fcntl O_NONBLOCK error: " + std::string(strerror(errno));
        return false;
    }

    return true;
}

bool NtServer::onRequest(NtContext* ctxPtr)
{
    std::cerr << "onRequest handler unimplemented." << std::endl;
    return false;
}

#ifdef NT_UNIX && !defined(NT_APPLE)
bool NtServer::controlEpoll(NtContext* ctxPtr, uint32_t events, int op)
{
    struct epoll_event ev_client{};
    ev_client.data.fd = ctxPtr->socket;
    ev_client.events = events;
    ev_client.data.ptr = ctxPtr;

    if (epoll_ctl(m_epFd, op, ctxPtr->socket, &ev_client) < 0) {
        std::lock_guard<std::mutex> lock(m_errMsgLock);
        m_errMsg = "kevent error: " + std::string(strerror(errno));
        return false;
    }

    return true;
}
#endif

bool NtServer::initTCPServer(const char* bindIP, int bindPort, size_t maxClients)
{
    m_sockUsage = NT_USAGE_TCP_SERVER;
    m_ip = bindIP;
    m_port = bindPort;
    m_maxClients = maxClients;

    if (maxClients < 0)
        return false;

    return runServer();
}

bool NtServer::runServer()
{
#ifdef NT_APPLE
    if (m_kqEventsPtr) {
#else
    if (m_epEvents) {
#endif
        std::lock_guard<std::mutex> lock(m_errMsgLock);
        m_errMsg = "server is already running.";
        return false;
    }

    if (m_sockUsage == NT_USAGE_IPC_SERVER)
        m_listenSocket = socket(AF_UNIX, SOCK_STREAM, 0);
    else if (m_sockUsage == NT_USAGE_TCP_SERVER)
        m_listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    else if (m_sockUsage == NT_USAGE_UDP_SERVER)
        m_listenSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (m_listenSocket < 0) {
        std::lock_guard<std::mutex> lock(m_errMsgLock);
        m_errMsg = "initialization error: " + std::string(strerror(errno));
        return false;
    }

    if (!setSocketNonBlocking(m_listenSocket))
        return false;

    int opt_on = 1;
    int result = -1;

    if (setsockopt(m_listenSocket, SOL_SOCKET, SO_REUSEADDR, &opt_on, sizeof(opt_on)) == -1) {
        std::lock_guard<std::mutex> lock(m_errMsgLock);
        m_errMsg = "setsockopt SO_REUSEADDR error: " + std::string(strerror(errno));
        return false;
    }

    if (setsockopt(m_listenSocket, SOL_SOCKET, SO_KEEPALIVE, &opt_on, sizeof(opt_on)) == -1) {
        std::lock_guard<std::mutex> lock(m_errMsgLock);
        m_errMsg = "setsockopt SO_KEEPALIVE error: " + std::string(strerror(errno));
        return false;
    }

    if (m_sockUsage == NT_USAGE_IPC_SERVER) {
        sockaddr_un ipcServerAddr;
        memset((void*)&ipcServerAddr, 0, sizeof(ipcServerAddr));
        ipcServerAddr.sun_family = AF_UNIX;
        snprintf(ipcServerAddr.sun_path, sizeof(ipcServerAddr.sun_path),
                "%s", m_serverIpcSocketPath.c_str());
        result = bind(m_listenSocket, (sockaddr*)&ipcServerAddr, sizeof(ipcServerAddr));
    } else if (m_sockUsage == NT_USAGE_TCP_SERVER || m_sockUsage == NT_USAGE_UDP_SERVER) {
        sockaddr_in serverAddr;
        memset((void*)&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = inet_addr(m_ip.c_str());
        serverAddr.sin_port = htons(m_port);
        result = bind(m_listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    }

    if (result < 0) {
        m_errMsg = "could not bind() to socket: " + std::string(strerror(errno));
        return false;
    }

    if (m_sockUsage == NT_USAGE_IPC_SERVER || m_sockUsage == NT_USAGE_TCP_SERVER) {
        result = listen(m_listenSocket, SOMAXCONN);

        if (result < 0) {
            std::lock_guard<std::mutex> lock(m_errMsgLock);
            m_errMsg = "listen error: " + std::string(strerror(errno));
            return false;
        }
    }

    struct sigaction act;
    act.sa_handler = SIG_IGN;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGPIPE, &act, NULL);

    m_listenContextPtr = new (std::nothrow) NtContext();

    if (!m_listenContextPtr) {
        std::lock_guard<std::mutex> lock(m_errMsgLock);
        m_errMsg = "Could not allocate context.";
        return false;
    }

    m_listenContextPtr->socket = m_listenSocket;

#ifdef NT_APPLE
    m_kqFd = kqueue();

    if (m_kqFd == -1) {
        std::lock_guard<std::mutex> lock(m_errMsgLock);
        m_errMsg = "kqueue error: " + std::string(strerror(errno));
        return false;
    }

    if (!controlKq(m_listenContextPtr, EVFILT_READ, EV_ADD))
        return false;
#else
    m_epFd = epoll_create1(0);

    if (m_epFd == -1) {
        std::lock_guard<std::mutex> lock(m_errMsgLock);
        m_errMsg = "epoll create error: " + std::string(strerror(errno));
        return false;
    }

    if (!controlEpoll(m_listenContextPtr, EPOLLIN | EPOLLERR, EPOLL_CTL_ADD))
        return false;
#endif

#ifdef NT_APPLE
    m_kqEventsPtr = new struct kevent[m_maxClients];
    memset(m_kqEventsPtr, 0, sizeof(struct kevent) * m_maxClients);
#else
    m_epEvents = new struct epoll_event[m_maxClients];
    memset(m_epEvents, 0, sizeof(struct epoll_event) * m_maxClients);
#endif

    m_needServerRun = true;
    m_serverRunning = true;

    if (m_sockUsage == NT_USAGE_UDP_SERVER) {
        std::thread serverThread(&NtServer::serverThreadUdpHandler, this);
        serverThread.detach();
    } else {
        std::thread serverThread(&NtServer::serverThreadHandler, this);
        serverThread.detach();
    }
    return true;
}

void NtServer::serverThreadHandler()
{
#ifdef NT_APPLE
    struct timespec ts;
    ts.tv_sec = 1;
    ts.tv_nsec = 0;
#endif

    while (m_needServerRun) {
#ifdef NT_APPLE
        int eventCnt = kevent(m_kqFd, NULL, 0, m_kqEventsPtr, m_maxClients, &ts);

        if (eventCnt < 0) {
            std::lock_guard<std::mutex> lock(m_errMsgLock);
            m_errMsg = "kevent error: " + std::string(strerror(errno));
            m_serverRunning = false;
            return;
        }
#else
        int eventCnt = epoll_wait(m_epFd, m_epEvents, m_maxClients, 1000);

        if (eventCnt < 0) {
            std::lock_guard<std::mutex> lock(m_errMsgLock);
            m_errMsg = "epoll wait error: " + std::string(strerror(errno));
            m_serverRunning = false;
            return;
        }
#endif

        for (int i = 0; i < eventCnt; ++i) {
#ifdef NT_APPLE
            if (m_kqEventsPtr[i].ident == m_listenSocket) {
#else
            if (((NtContext*)m_epEvents[i].data.ptr)->socket == m_listenSocket) {
#endif
                if (!acceptNewClient()) {
                    std::cerr << "accept error: " << m_errMsg << std::endl;
                    return;
                }
            } else {
#ifdef NT_APPLE
                NtContext* ctxPtr = (NtContext*)m_kqEventsPtr[i].udata;
                if (m_kqEventsPtr[i].flags & EV_EOF) {
#else
                NtContext* ctxPtr = (NtContext*)m_epEvents[i].data.ptr;
                if (m_epEvents[i].events & EPOLLRDHUP || m_epEvents[i].events & EPOLLERR) {
#endif
                    terminateClient(ctxPtr);
                }
#ifdef NT_APPLE
                else if (EVFILT_READ == m_kqEventsPtr[i].filter) {
#else
                else if (m_epEvents[i].events & EPOLLIN) {
#endif
                    if (!recvData(ctxPtr))
                        terminateClient(ctxPtr);
                }
#ifdef NT_APPLE
                else if (EVFILT_WRITE == m_kqEventsPtr[i].filter) {
#else
                else if (m_epEvents[i].events & EPOLLOUT) {
#endif
                    if (!sendPendingData(ctxPtr))
                        return;
                }
            }
        }
    }

    m_serverRunning = false;
}

void NtServer::serverThreadUdpHandler()
{
}

void NtServer::terminateClient(NtContext* clientCtx, bool force)
{
    --m_numClients;

    if (force) {
        struct linger linger_struct;
        linger_struct.l_onoff = 1;
        linger_struct.l_linger = 0;
        setsockopt(clientCtx->socket, SOL_SOCKET, SO_LINGER, (char*)&linger_struct, sizeof(linger_struct));
    }

#ifdef NT_APPLE
    controlKq(clientCtx, EVFILT_READ, EV_DELETE);
#else
    controlEpoll(clientCtx, EPOLLIN | EPOLLERR | EPOLLRDHUP, EPOLL_CTL_DEL);
#endif

    close(clientCtx->socket);

    onDisconnect(clientCtx);
    pushClientContextToCache(clientCtx);
}

bool NtServer::acceptNewClient()
{
    while (1) {
        int clientFd = -1;

        if (m_sockUsage == NT_USAGE_IPC_SERVER) {
            sockaddr_un clientAddr;
            socklen_t clientAddrSize = sizeof(clientAddr);
            clientFd = accept(m_listenSocket, (sockaddr*)&clientAddr, &clientAddrSize);
        } else if (m_sockUsage == NT_USAGE_TCP_SERVER) {
            sockaddr_in clientAddr;
            socklen_t clientAddrSize = sizeof(clientAddr);
            clientFd = accept(m_listenSocket, (sockaddr*)&clientAddr, &clientAddrSize);
        }

        if (clientFd == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                break;
            } else if (errno == ECONNABORTED) {
                break;
            } else {
                std::lock_guard<std::mutex> lock(m_errMsgLock);
                m_errMsg = "accept error: " + std::string(strerror(errno));
                m_serverRunning = false;
                return false;
            }
        }

        ++m_numClients;

        setSocketNonBlocking(clientFd);
        NtContext* clientContextPtr = popClientContextFromCache();

        if (clientContextPtr == nullptr) {
            m_serverRunning = false;
            return false;
        }

        clientContextPtr->socket = clientFd;
        clientContextPtr->isConnected = true;
        clientContextPtr->dataLen = 4096;
        clientContextPtr->recvBuffer = nullptr;

        onConnect(clientContextPtr);

#ifdef NT_APPLE
        if (!controlKq(clientContextPtr, EVFILT_READ, EV_ADD)) {
#else
        if (!controlEpoll(clientContextPtr, EPOLLIN | EPOLLRDHUP, EPOLL_CTL_ADD)) {
#endif
            m_serverRunning = false;
            return false;
        }
    }

    return true;
}

bool NtServer::recvData(NtContext* ctxPtr)
{
    size_t len = ctxPtr->dataLen;
    ctxPtr->recvBuffer = (char*)malloc(len);
    memset(ctxPtr->recvBuffer, 0, len + 1);

    int recvdLen = recv(ctxPtr->socket, ctxPtr->recvBuffer, len, 0);

    if (recvdLen > 0) {
        ctxPtr->readLen = recvdLen;
        return onRequest(ctxPtr);
    } else {
        std::lock_guard<std::mutex> lock(m_errMsgLock);
        m_errMsg = "recv 0, client disconnected.";
        return false;
    }

    return true;
}

bool NtServer::sendPendingData(NtContext* ctxPtr)
{
    std::lock_guard<std::mutex> guard(ctxPtr->ctxLock);

    while (!ctxPtr->pendingSendDeque.empty()) {
        NtPendingSent pendingSent = ctxPtr->pendingSendDeque.front();
        int sentLen = 0;

        if (m_sockUsage == NT_USAGE_UDP_SERVER) {
            sentLen = sendto(ctxPtr->socket, pendingSent.pendingSentData, pendingSent.pendingSentLen,
                    0, (struct sockaddr*)&pendingSent.udpRemoteAddr,
                    sizeof(pendingSent.udpRemoteAddr));
        } else {
            sentLen = send(ctxPtr->socket, pendingSent.pendingSentData, pendingSent.pendingSentLen, 0);
        }

        if (sentLen > 0) {
            if (sentLen == (int)pendingSent.pendingSentLen) {
                delete[] pendingSent.pendingSentData;
                ctxPtr->pendingSendDeque.pop_front();

                if (ctxPtr->pendingSendDeque.empty()) {
                    ctxPtr->isSentPending = false;

#ifdef NT_APPLE
                    if (!controlKq(ctxPtr, EVFILT_WRITE, EV_DELETE) || !controlKq(ctxPtr, EVFILT_READ, EV_ADD)) {
#else
                    if (!controlEpoll(ctxPtr, EPOLLIN | EPOLLERR | EPOLLRDHUP, EPOLL_CTL_MOD)) {
#endif
                        m_serverRunning = false;
                        return false;
                    }
                    break;
                }
            } else {
                NtPendingSent partialPendingSent;
                int allocLen = pendingSent.pendingSentLen - sentLen;
                partialPendingSent.pendingSentData = new char[allocLen];
                partialPendingSent.pendingSentLen = allocLen;
                memcpy(partialPendingSent.pendingSentData,
                        pendingSent.pendingSentData + sentLen, allocLen);

                delete[] pendingSent.pendingSentData;
                ctxPtr->pendingSendDeque.pop_front();
                ctxPtr->pendingSendDeque.push_front(partialPendingSent);
                break;
            }
        } else if (sentLen < 0) {
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                break;
            } else if (errno != EINTR) {
                {
                    std::lock_guard<std::mutex> lock(m_errMsgLock);
                    m_errMsg = "send error: " + std::string(strerror(errno));
                }

                terminateClient(ctxPtr);
                break;
            }
        }
    }

    return true;
}

void NtServer::pushClientContextToCache(NtContext* ctxPtr)
{
    ctxPtr->recvBuffer = nullptr;
    ctxPtr->socket = -1;
    ctxPtr->isSentPending = false;
    ctxPtr->isConnected = false;
    ctxPtr->dataLen = 0;
    
    while (!ctxPtr->pendingSendDeque.empty()) {
        NtPendingSent pendingSent = ctxPtr->pendingSendDeque.front();
        delete[] pendingSent.pendingSentData;
        ctxPtr->pendingSendDeque.pop_front();
    }

    std::lock_guard<std::mutex> lock(m_ctxCacheLock);
    m_queueCtxCache.push(ctxPtr);
}

NtContext* NtServer::popClientContextFromCache()
{
    NtContext* ctxPtr = nullptr;

    {
        std::lock_guard<std::mutex> lock(m_ctxCacheLock);
        if (!m_queueCtxCache.empty()) {
            ctxPtr = m_queueCtxCache.front();
            m_queueCtxCache.pop();
            return ctxPtr;
        }
    }

    ctxPtr = new (std::nothrow) NtContext();

    if (!ctxPtr) {
        std::lock_guard<std::mutex> lock(m_errMsgLock);
        m_errMsg = "Failed to allocate context.";
        return nullptr;
    }

    return ctxPtr;
}

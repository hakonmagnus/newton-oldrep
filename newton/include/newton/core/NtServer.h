// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtServer.h
 * \brief Server base definitions
 * \author Hákon Hjaltalín
 *
 * This file contains definitions for a server base class.
 */

#include "newton/base/NtDefs.h"

#include <atomic>
#include <string>
#include <mutex>
#include <thread>
#include <queue>
#include <iostream>

namespace newton
{

#ifdef NT_WINDOWS
using socket_t = SOCKET;
#else
using socket_t = int;
#endif

/**
 * \enum NtSockUsage
 * \brief Socket usage
 *
 * Type of socket server.
 */
enum NtSockUsage
{
    NT_USAGE_UNKNOWN = 0,
    NT_USAGE_TCP_SERVER,
    NT_USAGE_UDP_SERVER,
    NT_USAGE_IPC_SERVER
};

/**
 * \struct NtPendingSent
 * \brief Pending sent struct
 *
 * Structure for pending sent data.
 */
struct NtPendingSent
{
    char* pendingSentData;
    size_t pendingSentLen;
    sockaddr_in udpRemoteAddr;
};

#ifdef NT_WINDOWS
struct NtContext
{
    socket_t socket;
    int sockIdCopy{ -1 };
};
#else
/**
 * \struct NtContext
 * \brief Server context
 *
 * Various state variables
 */
struct NtContext
{
    socket_t socket;
    int sockIdCopy{ -1 };
    std::mutex ctxLock;
    char* recvBuffer;
    size_t dataLen{ 0 };
    size_t readLen{ 0 };
    bool isConnected{ false };
    bool isSentPending{ false };
    std::deque<NtPendingSent> pendingSendDeque;
    sockaddr_in udpRemoteAddr;
};
#endif

/**
 * \class NtServer
 * \brief Server base class
 *
 * This is the base class for a web server.
 */
class NT_EXPORT NtServer
{
public:
    /**
     * \brief Constructor
     *
     * Default constructor.
     */
    NtServer();

    /**
     * \brief Virtual destructor
     */
    virtual ~NtServer();

    /**
     * \brief Send data
     *
     * Send data over the socket.
     *
     * \param ctxPtr Context
     * \param buf Data buffer
     * \param len Buffer length
     */
    bool sendData(NtContext* ctxPtr, const char* buf, size_t len);

    /**
     * \brief Set socket to non-blocking
     *
     * Set socket to non-blocking mode.
     *
     * \param fd File descriptor
     * \return True on success
     */
    bool setSocketNonBlocking(int fd);

    /**
     * \brief On connect handler
     *
     * This function handles a new client connection.
     */
    virtual void onConnect(NtContext* ctx) { }

    /**
     * \brief On disconnect handler
     *
     * This function handles a client disconnecting.
     */
    virtual void onDisconnect(NtContext* ctx) { }

    /**
     * \brief On request handler
     *
     * This function handles a receive request.
     *
     * \param ctxPtr Context pointer
     * \return True on success
     */
    virtual bool onRequest(NtContext* ctxPtr);

    /**
     * \brief Initialize a TCP server.
     *
     * Initialize a new TCP server socket.
     *
     * \param bindIP Host IP address
     * \param bindPort Host port number
     * \param maxClients Maximum number of clients
     * \return True on success
     */
    bool initTCPServer(const char* bindIP, int bindPort, size_t maxClients = 100000);

protected:
#ifdef NT_WINDOWS
    bool recvData(size_t workerId, NtContext* ctxPtr, DWORD bytesTransferred);
#else
    bool recvData(NtContext* ctxPtr);
    bool sendPendingData(NtContext* ctxPtr);
#endif

#if defined(NT_WINDOWS)
    bool issueRecv(size_t workerIndex, NtContext* clientCtx);
#elif defined(NT_APPLE)
    bool controlKq(NtContext* ctxPtr, uint32_t events, uint32_t fflags);
#else
    bool controlEpoll(NtContext* ctrPtr, uint32_t events, int op);
#endif

    /**
     * \brief Terminate client
     *
     * Terminate a client connection.
     *
     * \param ctxPtr Context pointer
     * \param force Force close
     */
    void terminateClient(NtContext* ctxPtr, bool force = false);

protected:
    /**
     * Error message mutex
     */
    std::mutex m_errMsgLock;

    /**
     * Error message string
     */
    std::string m_errMsg;

    /**
     * Type of server
     */
    NtSockUsage m_sockUsage{ NT_USAGE_UNKNOWN };

#ifdef NT_APPLE
    struct kevent* m_kqEventsPtr{ nullptr };
    int m_kqFd{ -1 };
#elif defined(NT_WINDOWS)
    HANDLE m_handleCompletionPort;
#else
    struct epoll_event* m_epEvents{ nullptr };
    int m_epFd{ -1 };
#endif

private:
    /**
     * \brief Run server
     *
     * Run the server.
     *
     * \return True on success
     */
    bool runServer();

    /**
     * \brief UDP server thread
     *
     * UDP server thread handler.
     */
    void serverThreadUdpHandler();

    /**
     * \brief TCP server thread
     * 
     * TCP server thread handler.
     */
    void serverThreadHandler();

    /**
     * \brief Accept new client
     *
     * Accept a new client connection.
     *
     * \return True on success
     */
    bool acceptNewClient();

    /**
     * \brief Add to context cache
     *
     * Add client context to cache
     *
     * \param ctxPtr Context pointer
     */
    void pushClientContextToCache(NtContext* ctxPtr);

    /**
     * \”rief Pop from context cache
     *
     * Pop client context from cache
     *
     * \return Client context
     */
    NtContext* popClientContextFromCache();

private:
    /**
     * Is connected
     */
    std::atomic<bool> m_connected{ false };

    /**
     * IP string
     */
    std::string m_ip;

    /**
     * IPC path
     */
    std::string m_serverIpcSocketPath;

    /**
     * Port number
     */
    int m_port{ -1 };

    /**
     * Number of clients
     */
    std::atomic<int> m_numClients{ 0 };

    /**
     * Need to run server
     */
    std::atomic<bool> m_needServerRun{ true };

    /**
     * Is server currently running
     */
    std::atomic<bool> m_serverRunning{ false };

    /**
     * Maximum clients
     */
    size_t m_maxClients{ 0 };

    /**
     * Listen socket handle
     */
    socket_t m_listenSocket;

    /**
     * Context cache queue
     */
    std::queue<NtContext*> m_queueCtxCache;

    /**
     * Context cache lock
     */
    std::mutex m_ctxCacheLock;

#if defined(NT_APPLE) || defined(NT_UNIX)
    NtContext* m_listenContextPtr{ nullptr };
#endif
};

}


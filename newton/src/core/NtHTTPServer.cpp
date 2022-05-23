// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#include "newton/newton.h"
using namespace newton;

#include <iostream>

bool NtHTTPServer::onRequest(NtContext* ctxPtr)
{
    NtHTTPRequest* req = NtParseHTTPRequest(ctxPtr->recvBuffer, ctxPtr->dataLen);

    if (!req)
        return false;

    std::string host = m_defaultHost;
    NtHTTPHeader* hostHdr = req->getHeader("Host");
    NtHTTPResponse* resp = nullptr;
    
    if (hostHdr)
        host = hostHdr->value();

    if (m_hosts.find(host) != m_hosts.end()) {
        if (m_hosts[host]) {
            resp = m_hosts[host]->handleRequest(req);
        }
    }

    if (!resp)
        return false;

    std::string ret = resp->toString();

    if (!sendData(ctxPtr, ret.c_str(), ret.size())) {
        return false;
    }
    
    return true;
}

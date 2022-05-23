// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#include "newton/newton.h"
using namespace newton;

bool NtRoute::matchPath(const std::string& path)
{
    return m_path == path;
}

NtHTTPResponse* NtRoute::handleRequest(NtHTTPRequest* req)
{
    NtHTTPResponse* resp = new NtHTTPResponse("HTTP/1.1 200 OK");
    resp->addHeader(new NtHTTPHeader("Content-Length", "5"));
    
    char* body = new char[6];
    strcpy(body, "hello");
    resp->setBody(body);

    return resp;
}

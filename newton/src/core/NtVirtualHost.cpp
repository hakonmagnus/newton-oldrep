// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#include "newton/newton.h"
using namespace newton;

#include <iostream>

NtHTTPResponse* NtVirtualHost::handleRequest(NtHTTPRequest* req)
{
    std::string uri = req->requestURI();

    for (auto& r : m_routes) {
        if (r) {
            if (r->matchPath(uri)) {
                return r->handleRequest(req);
            }
        }
    }

    return nullptr;
}

// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtVirtualHost.h
 * \brief Virtual host definitions
 * \author Hákon Hjaltalín
 *
 * This file contains definitions for server virtual hosts.
 */

#include "newton/http/NtHTTPRequest.h"
#include "newton/http/NtHTTPResponse.h"
#include "newton/core/NtRoute.h"

#include <vector>

namespace newton
{

/**
 * \class NtVirtualHost
 * \brief Server virtual host
 *
 * This class defines a virtual host allowing programmers to use multiple
 * host names on the same server.
 */
class NT_EXPORT NtVirtualHost
{
public:
    /**
     * \brief Constructor
     *
     * Default constructor.
     *
     * \param host Hostname
     */
    NtVirtualHost(const std::string& host = "localhost")
        : m_host{ host }
    {
    }

    /**
     * \brief Virtual destructor
     */
    virtual ~NtVirtualHost() { }

    /**
     * \brief Add new route
     *
     * Add a route to this virtual host.
     *
     * \param route Route to add
     */
    void addRoute(NtRoute* route) { m_routes.push_back(route); }

    /**
     * \brief Handle HTTP request
     *
     * Function callback for handling HTTP requests.
     *
     * \param req HTTP request
     */
    virtual NtHTTPResponse* handleRequest(NtHTTPRequest* req);

    /**
     * \brief Get host name
     *
     * Get the host name associated with this virtual host.
     *
     * \return Virtual host name
     */
    std::string host() const { return m_host; }

protected:
    /**
     * Host name
     */
    std::string m_host;

    /**
     * List of routes
     */
    std::vector<NtRoute*> m_routes;
};

}


// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtHTTPServer.h
 * \brief HTTP server definitions
 * \author Hákon Hjaltalín
 *
 * This file contains definitions for an HTTP server.
 */

#include "newton/core/NtServer.h"
#include "newton/core/NtVirtualHost.h"

namespace newton
{

/**
 * \class NtHTTPServer
 * \brief HTTP server class
 *
 * This class defines an HTTP server over non-secure protocol.
 */
class NT_EXPORT NtHTTPServer : public NtServer
{
public:
    /**
     * \brief Constructor
     *
     * Default constructor.
     */
    NtHTTPServer()
        : m_defaultHost{ "localhost" }
    { }

    /**
     * \brief Handle request
     *
     * Handle TCP recv data
     *
     * \param ctxPtr Server context
     * \return True on success
     */
    virtual bool onRequest(NtContext* ctxPtr) override;

    /**
     * \brief Add virtual host
     *
     * Add a virtual host to this server.
     *
     * \param host Virtual host to add
     */
    void addHost(NtVirtualHost* host) { m_hosts.insert({ host->host(), host }); }

protected:
    /**
     * Default host value
     */
    std::string m_defaultHost;

    /**
     * Map of virtual hosts
     */
    std::map<std::string, NtVirtualHost*> m_hosts;
};

}


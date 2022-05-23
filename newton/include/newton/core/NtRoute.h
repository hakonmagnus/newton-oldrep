// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtRoute.h
 * \brief Server route definitions
 * \author Hákon Hjaltalín
 *
 * This file contains definitions for server routes.
 */

#include "newton/http/NtHTTPRequest.h"
#include "newton/http/NtHTTPResponse.h"

namespace newton
{

/**
 * \class NtRoute
 * \brief Server route class
 *
 * This class defines a server route along with its handlers.
 */
class NT_EXPORT NtRoute
{
public:
    /**
     * \brief Constructor
     *
     * Default constructor.
     *
     * \param path Route path
     */
    NtRoute(const std::string& path = "/")
        : m_path{ path }
    {
    }

    /**
     * \brief Check if path string matches this route
     *
     * Check whether a path string corresponds to this route.
     *
     * \param path Path to check
     * \return True if path belongs to this route
     */
    virtual bool matchPath(const std::string& path = "/");

    /**
     * \brief Handle HTTP request
     *
     * Handle an HTTP request along with a path string.
     *
     * \param req HTTP request
     * \return HTTP response object
     */
    NtHTTPResponse* handleRequest(NtHTTPRequest* req);

protected:
    /**
     * Route path
     */
    std::string m_path;
};

}


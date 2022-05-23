// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtHTTPResponse.h
 * \brief HTTP response definitions
 * \author Hákon Hjaltalín
 *
 * This fle contains definitions for HTTP responses extending HTTP messages.
 */

#include "newton/http/NtHTTPMessage.h"

namespace newton
{

/**
 * \class NtHTTPResponse.h
 * \brief HTTP response class
 *
 * This class defines an HTTP response.
 */
class NT_EXPORT NtHTTPResponse : public NtHTTPMessage
{
public:
    /**
     * \brief Constructor
     *
     * Default constructor.
     *
     * \param statusLine Status line
     */
    NtHTTPResponse(const std::string& statusLine = "")
        : NtHTTPMessage(Type::RESPONSE, statusLine)
    {
    }

    /**
     * \brief Virtual destructor
     */
    virtual ~NtHTTPResponse() { }
};

}


// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtHTTPRequest.h
 * \brief HTTP request definitons
 * \author Hákon Hjaltalín
 *
 * This file contains definitions for HTTP requests extending HTTP messages.
 */

#include "newton/http/NtHTTPMessage.h"

namespace newton
{

/**
 * \class NtHTTPRequest.h
 * \brief HTTP request class
 *
 * This class defines an HTTP request.
 */
class NT_EXPORT NtHTTPRequest : public NtHTTPMessage
{
public:
    /**
     * \enum RequestMethod
     * \brief HTTP request method
     *
     * This enum defines the different HTTP methods that are defined
     * by HTTP/1.1.
     */
    enum class RequestMethod
    {
        UNKNOWN,        ///< Unknown HTTP method
        OPTIONS,        ///< HTTP options method
        GET,            ///< HTTP get method
        HEAD,           ///< HTTP head method
        POST,           ///< HTTP post method
        PUT,            ///< HTTP put method
        DELETE,         ///< HTTP delete method
        TRACE,          ///< HTTP trace method
        CONNECT         ///< HTTP connect method
    };

    /**
     * \brief Constructor
     *
     * Default constructor.
     *
     * \param requestLine Request line
     */
    NtHTTPRequest(const std::string& requestLine = "")
        : NtHTTPMessage(Type::REQUEST, requestLine)
    {
        if (requestLine != "")
            parseRequestLine();
    }

    /**
     * \brief Virtual destructor
     */
    virtual ~NtHTTPRequest() { }

    /**
     * \brief Set request line
     *
     * Set HTTP request line.
     *
     * \param requestLine Request line to set
     */
    void setRequestLine(const std::string& requestLine = "")
    {
        setStartLine(requestLine);
        parseRequestLine();
    }

    /**
     * \brief Get request line
     *
     * Get the HTTP request line.
     *
     * \return HTTP request line
     */
    std::string requestLine() const { return startLine(); }

    /**
     * \brief Get request URI
     *
     * Get the HTTP request line URI string.
     *
     * \return HTTP request URI
     */
    std::string requestURI() const { return m_requestURI; }

    /**
     * \brief Get request method
     *
     * Get the HTTP request method
     *
     * \return HTTP request method
     */
    RequestMethod method() const { return m_method; }

    /**
     * \brief Get HTTP version
     *
     * Get the HTTP version
     *
     * \return HTTP version
     */
    NtHTTPVersion version() const { return m_version; }

protected:
    /**
     * Parse request line
     */
    void parseRequestLine();

protected:
    /**
     * Request method
     */
    RequestMethod m_method;

    /**
     * Request URI
     */
    std::string m_requestURI;

    /**
     * HTTP version
     */
    NtHTTPVersion m_version;
};

/**
 * \fn NtParseHTTPRequest
 * \brief Parse an HTTP request message
 *
 * Parse an HTTP request and return it as an object.
 *
 * \param buf Data buffer
 * \param len Length of data
 * \return HTTP request object
 */
NtHTTPRequest* NtParseHTTPRequest(char* buf, size_t len);

}


// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtHTTPMessage.h
 * \brief HTTP message class
 * \author Hákon Hjaltalín
 *
 * This file contains a base class definition for an HTTP message, which
 * is either an HTTP request or HTTP response.
 */

#include "newton/http/NtHTTPHeader.h"

#include <vector>

namespace newton
{

/**
 * \class NtHTTPVersion
 * \brief Version of HTTP
 *
 * This enum class describes the HTTP version of messages.
 */
enum class NtHTTPVersion
{
    HTTP_VERSION_UNKNOWN,
    HTTP_0_9,
    HTTP_1_0,
    HTTP_1_1,
    HTTP_2_0,
    HTTP_3_0
};

/**
 * \class NtHTTPMessage
 * \brief An HTTP message
 *
 * This class defines an HTTP message, which is either a request or a
 * response.
 */
class NT_EXPORT NtHTTPMessage
{
public:
    /**
     * \enum Type
     * \brief Type of message
     *
     * This enum specifies the type of HTTP message.
     */
    enum class Type
    {
        REQUEST,            ///< HTTP request message
        RESPONSE            ///< HTTP response message
    };

    /**
     * \brief Constructor
     *
     * Default constructor.
     *
     * \param startLine HTTP start line for message
     */
    NtHTTPMessage(Type type, const std::string& startLine = "")
        : m_type{ type }, m_startLine{ startLine }, m_headers{}, m_body{ nullptr }
    {
    }

    /**
     * \brief Virtual destructor
     */
    virtual ~NtHTTPMessage() { }

    /**
     * \brief Set the start line
     *
     * Set the HTTP start line.
     *
     * \param startLine Start line to set
     */
    void setStartLine(const std::string& startLine = "") { m_startLine = startLine; }

    /**
     * \brief Get the start line
     *
     * Get the HTTP start line.
     *
     * \return HTTP start line.
     */
    std::string startLine() const { return m_startLine; }

    /**
     * \brief Get header count
     *
     * Get the number of headers.
     *
     * \return Number of headers
     */
    size_t headerCount() const { return m_headers.size(); }

    /**
     * \brief Add header
     *
     * Add HTTP header to this message.
     *
     * \param header Header to add
     */
    void addHeader(NtHTTPHeader* header)
    {
        m_headers.push_back(header);
    }

    /**
     * \brief Remove header
     *
     * Remove HTTP header by name.
     *
     * \param name Header name to remove.
     */
    void removeHeader(const std::string& name)
    {
        auto it = std::find_if(m_headers.begin(), m_headers.end(), [&name](NtHTTPHeader*& hdr) {
            return hdr->name() == name;
        });

        if (it != m_headers.end()) {
            m_headers.erase(it);
        }
    }

    /**
     * \brief Get header by name
     *
     * Get HTTP header by name.
     *
     * \param name Header name
     * \return HTTP header
     */
    NtHTTPHeader* getHeader(const std::string& name)
    {
        auto it = std::find_if(m_headers.begin(), m_headers.end(), [&name](NtHTTPHeader*& hdr) {
            return hdr->name() == name;
        });

        if (it != m_headers.end()) {
            return *it;
        } else {
            return nullptr;
        }
    }

    /**
     * \brief Set message body
     *
     * Set the body of the HTTP message.
     *
     * \param body Body to set
     */
    void setBody(char* body = nullptr) { m_body = body; }

    /**
     * \brief Get message body
     *
     * Get the body of the HTTP message.
     *
     * \return Message body
     */
    char* body() const { return m_body; }
    
    /**
     * \brief Get the type
     *
     * Get HTTP message type.
     *
     * \return Message type
     */
    Type type() const { return m_type; }

    /**
     * \brief Convert message to string
     *
     * Convert this HTTP message to a string and return it.
     *
     * \return Message string
     */
    std::string toString() const
    {
        std::string ret = m_startLine;
        ret += "\r\n";

        for (auto& h : m_headers) {
            ret += h->name();
            ret += ": ";
            ret += h->value();
            ret += "\r\n";
        }

        ret += "\r\n";

        if (m_body) {
            ret += m_body;
        }
        
        return ret;
    }

protected:
    /**
     * HTTP message type
     */
    Type m_type;
    
    /**
     * HTTP start line
     */
    std::string m_startLine;

    /**
     * HTTP headers
     */
    std::vector<NtHTTPHeader*> m_headers;

    /**
     * Message body
     */
    char* m_body;
};

}


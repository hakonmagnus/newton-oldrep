// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtHTTPHeader.h
 * \brief HTTP header definitions
 * \author Hákon Hjaltalín
 *
 * This file contains a class definition for HTTP headers.
 */

#include "newton/base/NtDefs.h"

#include <string>

namespace newton
{

/**
 * \class NtHTTPHeader
 * \brief HTTP header class
 *
 * This class defines a single HTTP header object.
 */
class NT_EXPORT NtHTTPHeader
{
public:
    /**
     * \brief Constructor
     *
     * Default constructor.
     *
     * \param name Header name
     * \param value Header value
     */
    NtHTTPHeader(const std::string& name = "", const std::string& value = "")
        : m_name{ name }, m_value{ value }
    {
    }

    /**
     * \brief Virtual destructor
     */
    virtual ~NtHTTPHeader() { }

    /**
     * \brief Set header name
     *
     * Set the name for the header.
     *
     * \param name Name to set
     */
    void setName(const std::string& name = "") { m_name = name; }

    /**
     * \brief Get header name
     *
     * Get the name of the header.
     *
     * \return Header name
     */
    std::string name() const { return m_name; }

    /**
     * \brief Set header value
     *
     * Set the value for the header.
     *
     * \param value Value to set
     */
    void setValue(const std::string& value = "") { m_value = value; }

    /**
     * \brief Get header value
     *
     * Get the value for the header.
     *
     * \return Header value
     */
    std::string value() const { return m_value; }

private:
    /**
     * Header name
     */
    std::string m_name;

    /**
     * Header value
     */
    std::string m_value;
};

}


// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtException.h
 * \brief Exception classes
 * \author Hákon Hjaltalín
 *
 * This file contains definitions for exceptions and errors.
 */

#include "newton/base/NtDefs.h"
#include <string>
#include <exception>

namespace newton
{

class NT_EXPORT NtException : public std::exception
{
public:
    virtual std::string message()
    {
        return "Newton Exception.";
    }
};

class NT_EXPORT NtSyntaxError : public NtException
{
public:
    /**
     * \brief Constructor
     *
     * Default constructor with message.
     *
     * \param msg Message string
     */
    NtSyntaxError(const std::string& msg)
        : m_msg{ msg }
    {
    }

    /**
     * \brief Get exception message
     *
     * Get the exception message.
     *
     * \return Exception message
     */
    virtual std::string message() override
    {
        std::string str = "Newton Syntax Error: ";
        str += m_msg;
        return str;
    }

protected:
    /**
     * Message string
     */
    std::string m_msg;
};

class NT_EXPORT NtRuntimeException : public NtException
{
public:
    /**
     * \brief Constructor
     *
     * Default constructor with message.
     *
     * \param msg Message string
     */
    NtRuntimeException(const std::string& msg)
        : m_msg{ msg }
    {
    }

    /**
     * \brief Get exception message
     *
     * Get the exception message.
     *
     * \return Exception message
     */
    virtual std::string message() override
    {
        std::string str = "Newton Runtime Exception: ";
        str += m_msg;
        return str;
    }

protected:
    /**
     * Message string
     */
    std::string m_msg;
};

}


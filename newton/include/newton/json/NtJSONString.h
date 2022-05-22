// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtJSONString.h
 * \brief JSON string
 * \author Hákon Hjaltalń
 *
 * This file contains a class definition for a JSON string.
 */

#include "newton/json/NtJSONElement.h"
#include <string>
#include <sstream>

namespace newton
{

/**
 * \class NtJSONString
 * \brief JSON string class
 *
 * This class defines a JSON string.
 */
class NT_EXPORT NtJSONString : public NtJSONElement
{
public:
    /**
     * \brief Constructor
     *
     * Default constructor with string argument.
     *
     * \param value String value
     */
    NtJSONString(const std::string& value = "")
        : NtJSONElement(Type::STRING), m_value{ value }
    {
    }

    /**
     * \brief Constructor
     *
     * Constructor from numeric value.
     *
     * \param value Numeric value
     */
    NtJSONString(const double value = 0.0)
        : NtJSONElement(Type::STRING)
    {
        std::stringstream ss;
        ss << value;
        m_value = ss.str();
    }
    
    /**
     * \brief Destructor
     */
    ~NtJSONString() { }

    /**
     * \brief Set string value
     *
     * Set string value to a string.
     *
     * \param value Value to set
     */
    void setValue(const std::string& value)
    {
        m_value = value;
    }

    /**
     * \brief Set numeric value
     *
     * Set string to a numeric value.
     *
     * \tparam T Type of value
     * \param value Value to set
     */
    template <typename T>
    void setValue(const T value)
    {
        std::stringstream sstr;
        sstr << value;
        m_value = sstr.str();
    }

    /**
     * \brief Convert to number
     *
     * Convert this string to a number and return.
     *
     * \return String as number
     */
    double toNumber() const
    {
        return atof(m_value.c_str());
    }

    /**
     * \brief Get value
     *
     * Get the string value associated with this JSON string object.
     *
     * \return String value
     */
    std::string value() const { return m_value; }

private:
    /**
     * String value
     */
    std::string m_value;
};

}


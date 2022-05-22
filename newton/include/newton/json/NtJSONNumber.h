// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtJSONNumber.h
 * \brief JSON number
 * \author Hákon Hjaltalín
 *
 * This file contains a class definition for a JSON number.
 */

#include "newton/json/NtJSONElement.h"
#include <string>
#include <sstream>

namespace newton
{

/**
 * \class NtJSONNumber
 * \brief JSON number class
 *
 * This class defines a JSON number.
 */
class NT_EXPORT NtJSONNumber : public NtJSONElement
{
public:
    /**
     * \brief Constructor
     *
     * Default constructor with number argument.
     *
     * \param value Numeric value
     */
    NtJSONNumber(const double value = 0.0)
        : NtJSONElement(Type::NUMBER), m_value{ value }
    {
    }

    /**
     * \brief Constructor from string
     *
     * Constructor from string value.
     *
     * \param value String value
     */
    NtJSONNumber(const char* value)
        : NtJSONElement(Type::NUMBER)
    {
        m_value = atof(value);
    }

    /**
     * \brief Destructor
     */
    ~NtJSONNumber() { }

    /**
     * \brief Set string value
     *
     * Set string value.
     *
     * \param value Value to set
     */
    void setValue(const char* value)
    {
        m_value = atof(value);
    }

    /**
     * \brief Set numeric value
     *
     * Set numeric value.
     *
     * \tparam T Numeric type
     * \param value Value to set
     */
    template <typename T>
    void setValue(const T value)
    {
        m_value = static_cast<double>(value);
    }

    /**
     * \brief Convert to string
     *
     * Convert numeric value to string and return.
     *
     * \return String value
     */
    std::string toString() const
    {
        std::stringstream ss;
        ss << m_value;
        return ss.str();
    }

    /**
     * \brief Get numeric value
     *
     * Get the numeric value associated with this JSON number object.
     *
     * \return Numeric value
     */
    double value() const { return m_value; }

private:
    /**
     * Numeric value
     */
    double m_value;
};

}


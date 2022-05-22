// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtJSONBoolean.h
 * \brief JSON boolean
 * \author Hákon Hjaltalín
 *
 * This file contains the class definition for a JSON boolean.
 */

#include "newton/json/NtJSONElement.h"
#include <string>

namespace newton
{

/**
 * \class NtJSONBoolean
 * \brief JSON boolean class
 *
 * This class defines a JSON boolean.
 */
class NT_EXPORT NtJSONBoolean : public NtJSONElement
{
public:
    /**
     * \brief Constructor
     *
     * Default constructor with boolean argument.
     *
     * \param value Boolean value
     */
    NtJSONBoolean(bool value = false)
        : NtJSONElement(Type::BOOLEAN), m_value{ value }
    {
    }

    /**
     * \brief Constructor from string
     *
     * Constructor from string value.
     *
     * \param value String value
     */
    NtJSONBoolean(const std::string& value)
        : NtJSONElement(Type::BOOLEAN)
    {
        if (value == "true") {
            m_value = true;
        } else {
            m_value = false;
        }
    }

    /**
     * \brief Destructor
     */
    ~NtJSONBoolean() { }

    /**
     * \brief Set boolean value
     *
     * Set boolean value.
     *
     * \param value Value to set
     */
    void setValue(bool value = false)
    {
        m_value = value;
    }

    /**
     * \brief Set string value
     *
     * Set string value.
     *
     * \param value Value to set
     */
    void setValue(const std::string& value)
    {
        if (value == "true") {
            m_value = true;
        } else {
            m_value = false;
        }
    }

    /**
     * \brief Set other value
     *
     * Set any other kind of value.
     *
     * \tparam T Type of value
     * \param value Value to set
     */
    template <typename T>
    void setValue(T value)
    {
        m_value = !!value;
    }

    /**
     * \brief Get value
     *
     * Get boolean value associated with this JSON boolean.
     *
     * \return Boolean value
     */
    bool value() const { return m_value; }

private:
    /**
     * Boolean value
     */
    bool m_value;
};

}


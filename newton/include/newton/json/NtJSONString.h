// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtJSONString.h
 * \brief JSON string
 *
 * This file contains the class definition for a JSON string.
 */

#include "newton/json/NtJSONElement.h"
#include <string>
#include <sstream>
#include <utility>
#include <cstdlib>

namespace newton
{

/**
 * \class NtJSONString
 * \brief JSON string element
 *
 * This class defines a JSON string element.
 */
class NT_EXPORT NtJSONString : public NtJSONElement
{
public:
    /**
     * \brief Default constructor
     *
     * Default constructor taking a value.
     *
     * \param value Value to set
     */
    NtJSONString(const std::string& value = "") :
        NtJSONElement(Type::STRING), m_value{ value }
    {
    }

    /**
     * \brief Copy constructor
     * \param other Other NtJSONString
     */
    NtJSONString(const NtJSONString& other) :
        NtJSONElement(Type::STRING), m_value{ other.m_value }
    {
    }

    /**
     * \brief Move constructor
     * \param other Other NtJSONString
     */
    NtJSONString(NtJSONString&& other) :
        NtJSONElement(Type::STRING), m_value{ std::move(other.m_value) }
    {
    }

    /**
     * \brief Virtual destructor
     */
    virtual ~NtJSONString() { }

    /**
     * \brief Copy assignment
     * \param other Other NtJSONString
     * \return Reference to this
     */
    NtJSONString& operator=(const NtJSONString& other)
    {
        m_type = other.m_type;
        m_value = other.m_value;
        return *this;
    }

    /**
     * \brief Move assignment
     * \param other Other NtJSONString
     * \return Reference to this
     */
    NtJSONString& operator=(NtJSONString&& other)
    {
        m_type = std::move(other.m_type);
        m_value = std::move(other.m_value);
        return *this;
    }

    /**
     * \brief Assignment from std::string
     * 
     * Assigns a value to this class using an std::string value.
     *
     * \param str Strnig to set
     * \return Reference to this
     */
    NtJSONString& operator=(const std::string& str)
    {
        m_value = str;
        return *this;
    }

    /**
     * \brief Get value
     * 
     * Get the value associated with this class.
     *
     * \return String value
     */
    std::string value() const { return m_value; }

    /**
     * \brief Set value
     *
     * Set the value associated with this class.
     *
     * \param value Value to set
     */
    void setValue(const std::string& value) { m_value = value; }

    /**
     * \brief Set value from C-string
     *
     * Set the value from a C-style string.
     *
     * \param value Value to set
     */
    void setValue(const char* value) { m_value = value; }

    /**
     * \brief Convert to number
     *
     * Convert this string to a number
     *
     * \return This string as a number
     */
    double toNumber() const
    {
        return atof(m_value.c_str());
    }

    /**
     * \brief Set value from number
     *
     * Convert a number into a string and store in this value.
     *
     * \param num Number to set
     */
    void fromNumber(const double num)
    {
        std::ostringstream strs;
        strs << num;
        m_value = strs.str();
    }

    /**
     * \brief Comparison operator
     *
     * Compare if this class is equal to another
     *
     * \param other Other NtJSONString
     * \return True if equal
     */
    bool operator==(const NtJSONString& other) const { return m_value == other.m_value; }

    /**
     * \brief Comparison operator
     *
     * Compare if this class is not equal to another
     *
     * \param other Other NtJSONString
     * \return False if equal
     */
    bool operator!=(const NtJSONString& other) const { return m_value != other.m_value; }

    /**
     * \brief Comparison operator
     *
     * Compare if this class is equal to an std::string
     *
     * \param str String to compare
     * \return True if equal
     */
    bool operator==(const std::string& str) const { return m_value == str; }

    /**
     * \brief Comparison operator
     *
     * Compare if this class is not equal to an std::string
     *
     * \param str String to compare
     * \return False if equal
     */
    bool operator!=(const std::string& str) const { return m_value != str; }
    
private:
    /**
     * String value
     */
    std::string m_value;
};

}


// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtJSONBoolean.h
 * \brief JSON boolean
 *
 * This file contains the class definition for a JSON boolean value.
 */

#include "newton/json/NtJSONElement.h"
#include "newton/base/NtException.h"
#include <utility>

namespace newton
{

/**
 * \class NtJSONBoolean
 * \brief JSON boolean element
 *
 * This class defines a JSON boolean value element.
 */
class NT_EXPORT NtJSONBoolean : public NtJSONElement
{
public:
    /**
     * \brief Default constructor
     *
     * Default constructor taking a value.
     *
     * \param value Value to set
     */
    NtJSONBoolean(bool value = false) :
        NtJSONElement(Type::BOOLEAN), m_value{ value }
    {
    }

    /**
     * \brief Copy constructor
     * \param other Other NtJSONBoolean
     */
    NtJSONBoolean(const NtJSONBoolean& other) :
        NtJSONElement(Type::BOOLEAN), m_value{ other.m_value }
    {
    }

    /**
     * \brief Move constructor
     * \param other Other NtJSONBoolean
     */
    NtJSONBoolean(NtJSONBoolean&& other) :
        NtJSONElement(Type::BOOLEAN), m_value{ std::move(other.m_value) }
    {
    }

    /**
     * \brief Virtual destructor
     */
    virtual ~NtJSONBoolean() { }

    /**
     * \brief Copy assignment
     * \param other Other NtJSONBoolean
     * \return Reference to this
     */
    NtJSONBoolean& operator=(const NtJSONBoolean& other)
    {
        m_type = other.m_type;
        m_value = other.m_value;
        return *this;
    }

    /**
     * \brief Move assignment
     * \param other Other NtJSONBoolean
     * \return Reference to this
     */
    NtJSONBoolean& operator=(NtJSONBoolean&& other)
    {
        m_type = std::move(other.m_type);
        m_value = std::move(other.m_value);
        return *this;
    }

    /**
     * \brief Assignment from string
     *
     * This assignment operator takes a string containing either "true"
     * or "false" and sets the value accordingly.
     *
     * \param str String to set
     * \return Reference to this
     */
    NtJSONBoolean& operator=(const std::string& str)
    {
        if (str == "true")
        {
            m_value = true;
        }
        else if (str == "false")
        {
            m_value = false;
        }
        else
        {
            throw NtInvalidArgument("String must be 'true' or 'false'.");
        }
        return *this;
    }

    /**
     * \brief Assignment from C-style string
     *
     * This assignment operator calls the assignment operator for
     * std::string.
     *
     * \param str String to set
     * \return Reference to this
     */
    NtJSONBoolean& operator=(const char* str)
    {
        return operator=(std::string(str));
    }

    /**
     * \brief Assignment from some value
     *
     * This assignment operator takes a template value which can be any type
     * and converts it into a boolean.
     *
     * \tparam T Type to convert
     * \param val Value to assign
     * \return Reference to this
     */
    template <typename T>
    NtJSONBoolean& operator=(const T& val)
    {
        m_value = val ? true : false;
        return *this;
    }

    /**
     * \brief Get value
     *
     * Get the value associated with this class.
     *
     * \return Boolean value
     */
    bool value() const { return m_value; }

    /**
     * \brief Set value
     *
     * Set the value associated with this class.
     *
     * \param value Value to set
     */
    void setValue(bool value) { m_value = value; }

    /**
     * \brief Set value from string
     *
     * This will set the value to "true" for a string "true" and vice
     * versa.
     *
     * \param str String to set
     */
    void setValue(const std::string& str)
    {
        if (str == "true")
        {
            m_value = true;
        }
        else if (str == "false")
        {
            m_value = false;
        }
        else
        {
            throw NtInvalidArgument("String must be 'true' or 'false'.");
        }
    }

    /**
     * \brief Set value from C-style string
     *
     * This will call the setValue function for std::string.
     *
     * \param str String to set
     */
    void setValue(const char* str)
    {
        setValue(std::string(str));
    }

    /**
     * \brief Set value from other type
     *
     * This function uses a template to convert an arbitrary type
     * into a boolean.
     *
     * \tparam T Type to convert
     * \param value Value to set
     */
    template <typename T>
    void setValue(const T& value)
    {
        m_value = value ? true : false;
    }

    /**
     * \brief Convert to string
     *
     * Convert this boolean to either the string "true" or the string "false".
     *
     * \return Boolean value as string
     */
    std::string toString() const
    {
        return m_value ? "true" : "false";
    }

    /**
     * \brief Comparison operator
     *
     * Compare if this class is equal to another
     *
     * \param other Other NtJSONBoolean
     * \return True if equal
     */
    bool operator==(const NtJSONBoolean& other) const { return m_value == other.m_value; }

    /**
     * \brief Comparison operator
     *
     * Compare if this class is not equal to another
     *
     * \param other Other NtJSONBoolean
     * \return False if equal
     */
    bool operator!=(const NtJSONBoolean& other) const { return m_value != other.m_value; }

    /**
     * \brief Comparison operator
     *
     * Compare if this class is equal to an std::string
     *
     * \param str String to compare
     * \return True if str is same boolean value as this class
     */
    bool operator==(const std::string& str) const
    {
        if (str == "true")
        {
            return m_value;
        }
        else if (str == "false")
        {
            return !m_value;
        }
        else
        {
            throw NtInvalidArgument("String must be 'true' or 'false'.");
        }
    }

    /**
     * \brief Comparison operator
     *
     * Compare if this class is not equal to an std::string
     *
     * \param str String to compare
     * \return False if str is same boolean value as this class
     */
    bool operator!=(const std::string& str) const { return !operator==(str); }

    /**
     * \brief Comparison operator
     *
     * Compare if this class is equal to a C-style string
     *
     * \param str String to compare
     * \return True if str is same boolean value as this class
     */
    bool operator==(const char* str) const { return operator==(std::string(str)); }

    /**
     * \brief Comparison operator
     *
     * Compare if this class is not equal to a C-style string
     *
     * \param str String to compare
     * \return False if str is same boolean value as this class
     */
    bool operator!=(const char* str) const { return !operator==(str); }

    /**
     * \brief Comparison operator
     *
     * This comparison operator takes a template type and converts it
     * to boolean before comparing to this class.
     *
     * \tparam T Type to compare
     * \param val Value of type T
     * \return True if val is same boolean value as this class
     */
    template <typename T>
    bool operator==(const T& val) const
    {
        if (!val) {
            return !m_value;
        } else {
            return m_value;
        }
    }

    /**
     * \brief Comparison operator
     *
     * Template comparison operator converting the type to
     * boolean before comparing. Inequality.
     *
     * \tparam T Type to compare
     * \param val Value of type T
     * \return False if val is same boolean value as this class
     */
    template <typename T>
    bool operator!=(const T& val) const { return !operator==(val); }

private:
    /**
     * Boolean value
     */
    bool m_value;
};

}


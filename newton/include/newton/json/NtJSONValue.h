// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtJSONValue.h
 * \brief JSON value
 *
 * This file contains the class definition for a JSON value.
 */

#include "newton/base/NtDefs.h"

namespace newton
{
/**
 * \class NtJSONValue
 * \brief JSON value class
 *
 * This class defines a value as defined in the JSON spec.
 *
 * \tparam T Value underlying type
 */
template <typename T>    
class NT_EXPORT NtJSONValue
{
public:
    /**
     * \enum JSON value type
     * \brief Type of JSON value
     */
    enum class Type
    {
        OBJECT,
        ARRAY,
        STRING,
        NUMBER,
        BOOLEAN,
        NUL
    };

    /**
     * \brief Constructor
     *
     * Default constructor. Takes in a NtJSONValue::Type specifying the type
     * of JSON value.
     *
     * \param type Type of JSON value
     */
    explicit NtJSONValue(const Type type) :
        m_type{ type }
    {
    }
    
    /**
     * \brief Copy constructor
     *
     * Copy constructor for JSON value.
     *
     * \param other Other JSON value
     */
    NtJSONValue(const NtJSONValue<T>& other) :
        m_type{ other.m_type }, m_value{ other.m_value }
    {
    }

    /**
     * \brief Move constructor
     *
     * Move constructor for JSON value.
     *
     * \param other Other JSON value
     */
    NtJSONValue(NtJSONValue<T>&& other) :
        m_type{ std::move(other.m_type) }, m_value{ std::move(other.m_value) }
    {
    }

    /**
     * \brief Virtual destructor
     *
     * Destructor for JSON value
     */
    virtual ~NtJSONValue() { }

    /**
     * \brief Get value
     * 
     * Get the underlying value
     *
     * \return JSON value
     */
    virtual T value() const { return m_value; }

    /**
     * \brief Set value
     *
     * Set the underlying value
     *
     * \param value Value to set
     */
    virtual void setValue(const T value) { m_value = value; }

protected:
    /**
     * Type of value
     */
    Type m_type;

    /**
     * Value
     */
    T m_value;
};

}  // namespace newton

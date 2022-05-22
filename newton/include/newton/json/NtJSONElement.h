// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtJSONElement.h
 * \brief Element base class
 * \author Hákon Hjaltalín
 *
 * This file contains the base definition for a JSON element.
 */

#include "newton/base/NtDefs.h"

namespace newton
{

/**
 * \class NtJSONElement
 * \brief JSON element class
 *
 * This is the base class for all JSON elements.
 */
class NT_EXPORT NtJSONElement
{
public:
    /**
     * \enum Element type
     * \brief Type of element
     *
     * Enum class describing the element type of a JSON element.
     */
    enum class Type
    {
        OBJECT,     ///< JSON object
        ARRAY,      ///< JSON array
        STRING,     ///< JSON string
        NUMBER,     ///< JSON number
        BOOLEAN,    ///< JSON boolean
        NUL         ///< JSON null
    };

    /**
     * \brief Constructor
     *
     * Default constructor with type.
     */
    NtJSONElement(const Type type)
        : m_type{ type }
    {
    }

    /**
     * \brief Destructor
     *
     * Virtual destructor.
     */
    virtual ~NtJSONElement() { }

    /**
     * \brief Get type
     *
     * Get the type of JSON element.
     *
     * \return Element type
     */
    Type type() const { return m_type; }

protected:
    /**
     * Element type
     */
    Type m_type;
};

}


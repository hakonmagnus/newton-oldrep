// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtJSONNul.h
 * \brief JSON null
 *
 * This file contains the class definition for a JSON null value.
 */

#include "newton/json/NtJSONElement.h"

namespace newton
{

/**
 * \class NtJSONNul
 * \brief JSON null element
 *
 * This class defines a JSON null value element.
 */
class NT_EXPORT NtJSONNul : public NtJSONElement
{
public:
    /**
     * \brief Default constructor
     *
     * Default constructor.
     */
    NtJSONNul() : NtJSONElement(Type::NUL) { }

    /**
     * \brief Copy constructor
     * \param other Other NtJSONNul
     */
    NtJSONNul(const NtJSONNul& other) = default;

    /**
     * \brief Move constructor
     * \param other Other NtJSONNul
     */
    NtJSONNul(NtJSONNul&& other) = default;

    /**
     * \brief Virtual destructor
     */
    virtual ~NtJSONNul() { }

    /**
     * \brief Copy assignment
     * \param other Other NtJSONNul
     * \return Reference to this
     */
    NtJSONNul& operator=(const NtJSONNul& other) { return *this; }

    /**
     * \brief Move assignment
     * \param other Other NtJSONNul
     * \return Reference to this
     */
    NtJSONNul& operator=(NtJSONNul&& other) { return *this; }
};

}


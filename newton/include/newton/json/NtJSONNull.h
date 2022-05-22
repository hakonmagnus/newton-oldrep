// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtJSONNull.h
 * \brief JSON null value
 * \author Hákon Hjaltalín
 *
 * This file contains the class definition for a JSON null value.
 */

#include "newton/json/NtJSONElement.h"

namespace newton
{

/**
 * \class NtJSONNull
 * \brief JSON null value class
 *
 * This class defines a JSON null value.
 */
class NT_EXPORT NtJSONNull : public NtJSONElement
{
public:
    /**
     * \brief Constructor
     *
     * Default constructor.
     */
    NtJSONNull()
        : NtJSONElement(Type::NUL)
    {
    }

    /**
     * \brief Destructor
     */
    ~NtJSONNull() { }
};

}


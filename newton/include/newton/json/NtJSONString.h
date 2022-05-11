// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtJSONString.h
 * \brief JSON string value
 *
 * This file contains the class definition for a JSON string.
 */

#include "newton/json/NtJSONValue.h"
#include <string>

namespace newton
{

/**
 * \class NtJSONString
 * \brief JSON string
 *
 * This class definition represents a JSON string value.
 */
class NT_EXPORT NtJSONString : public NtJSONValue<std::string>
{
public:
    /**
     * \brief Default constructor
     *
     * Default constructor. Takes an std::string.
     *
     * \param value Value to set
     */
    NtJSONString(const std::string& value = "") :
        NtJSONValue<std::string>(NtJSONValue<std::string>::Type::STRING)
    {
        m_value = value;
    }

    /**
     * \brief Virtual destructor
     */
    virtual ~NtJSONString() { }
};

}


// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtString.h
 * \brief Various string utils
 * \author Hákon Hjaltalín
 *
 * This file contains various string utilities.
 */

#include "newton/base/NtDefs.h"
#include <string>
#include <algorithm>

namespace newton
{

static inline void NtLTrim(std::string& s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

static inline void NtRTrim(std::string& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

static inline void NtTrim(std::string& s)
{
    NtLTrim(s);
    NtRTrim(s);
}

}


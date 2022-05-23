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

/**
 * \enum Character encoding
 *
 * This enum defines classes of character encodings.
 */
enum NtUTFEncoding
{
    NT_UTF_UNKNOWN,     ///< Unknown encoding
    NT_UTF_8,           ///< UTF-8 encoding
    NT_UTF_16BE,        ///< UTF-16 Big-Endian
    NT_UTF_16LE         ///< UTF-16 Little-Endian
};

}


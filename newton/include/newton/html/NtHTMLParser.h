// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtHTMLParser.h
 * \brief HTML parser function
 *
 * This file defines the function for parsing HTML strings.
 */

#include "newton/dom/NtDocument.h"

namespace newton
{

NtDocument* NtParseHTML(const char* data, size_t size);

}


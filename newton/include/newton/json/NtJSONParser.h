// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtJSONParser.h
 * \brief JSON parser
 * \author Hákon Hjaltalín
 *
 * This file contains a declaration for the JSON parse function.
 */

#include "newton/json/NtJSONObject.h"
#include "newton/json/NtJSONArray.h"
#include "newton/json/NtJSONString.h"
#include "newton/json/NtJSONNumber.h"
#include "newton/json/NtJSONBoolean.h"
#include "newton/json/NtJSONNull.h"

namespace newton
{

NtJSONObject* NtParseJSON(const char* json);

}


// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#include "newton/newton.h"
using namespace newton;

NtUTFEncodiing NtHTMLFindEncoding(const char* data, size_t size)
{
    NtUTFEncoding enc = NtHTMLBOMSniff(data, size);
    return enc;
}

NtDocument* newton::NtParseHTML(const char* data, size_t size)
{
    NtUTFEncoding enc = NtHTMLFindEncoding(data, size);

    if (enc == NT_UTF_UNKNOWN)
        enc = NT_UTF_8;

    return nullptr;
}

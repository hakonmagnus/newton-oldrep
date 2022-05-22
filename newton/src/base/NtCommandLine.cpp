// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#include "newton/newton.h"
using namespace newton;

void NtCommandLine::parse(int& argc, char** argv)
{
    if (argc <= 1) {
        return;
    }
    
    for (int pos = 1; pos < argc; ++pos)
    {
        if (argv[pos][0] == '-') {
            if (pos + 1 < argc) {
                if (argv[pos + 1][0] == '-') {
                    m_arguments.insert({ argv[pos], "true" });
                } else {
                    m_arguments.insert({ argv[pos], argv[pos + 1] });
                    ++pos;
                }
            } else {
                m_arguments.insert({ argv[pos], "true" });
            }
        } else {
            m_commands.push_back(argv[pos]);
        }
    }
}

// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#include "newton/newton.h"
using namespace newton;

NtApplication::NtApplication() :
    m_isRunning{ false }
{
}

NtApplication::~NtApplication()
{
    m_isRunning = false;
}

bool NtApplication::onInit(int& argc, char** argv) {
    return true;
}

void NtApplication::onExit() {
}

int NtApplication::run() {
    return 0;
}


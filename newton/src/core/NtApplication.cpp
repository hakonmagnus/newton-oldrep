// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#include "newton/newton.h"
using namespace newton;

NtApplication* NtApplication::ms_instance{ nullptr };

NtApplication::NtApplication()
    : m_running{ false }, m_exitCode{ 0 }
{
    ms_instance = this;
}

NtApplication::~NtApplication()
{
    m_running = false;
    ms_instance = nullptr;
}

bool NtApplication::initialize(int& argc, char** argv)
{
    m_commandLine = new NtCommandLine(argc, argv);
    return onInit();
}

int NtApplication::run()
{
    m_running = true;

    while (m_running) {
    }

    onExit();
    return m_exitCode;
}

void NtApplication::exit(int code)
{
    m_exitCode = code;
    m_running = false;
}

bool NtApplication::onInit()
{
    return true;
}

void NtApplication::onExit()
{
}

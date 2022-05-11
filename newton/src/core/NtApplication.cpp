// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#include "newton/newton.h"
using namespace newton;

NtApplication* NtApplication::ms_instance{ nullptr };

NtApplication::NtApplication() :
    m_isRunning{ false }
{
    if (ms_instance) {
        throw NtInitializeError("An application instance has already been created.");
    }

    ms_instance = this;
}

NtApplication::~NtApplication()
{
    m_isRunning = false;
    ms_instance = nullptr;

#ifdef NT_WINDOWS
    WSACleanup();
#endif
}

bool NtApplication::onInit(int& argc, char** argv) {
    if (!ms_instance) {
        throw NtNullException("Application instance is null.");
    }

#ifdef NT_WINDOWS
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (iResult != 0) {
        throw NtInitializeError("WSAStartup failed: " + iResult);
    }
#endif

    return true;
}

void NtApplication::onExit() {
}

int NtApplication::run() {
    return 0;
}


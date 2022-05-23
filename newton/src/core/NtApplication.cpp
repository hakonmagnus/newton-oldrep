// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#include "newton/newton.h"
using namespace newton;

NtApplication* NtApplication::ms_instance{ nullptr };

NtApplication::NtApplication()
    : m_running{ false }, m_exitCode{ 0 }, m_httpServer{ nullptr }
{
    ms_instance = this;
}

NtApplication::~NtApplication()
{
    if (m_httpServer) {
        delete m_httpServer;
        m_httpServer = nullptr;
    }

    for (int i = 0; i < m_virtualHosts.size(); ++i) {
        delete m_virtualHosts[i];
        m_virtualHosts[i] = nullptr;
    }

    m_running = false;
    ms_instance = nullptr;
}

bool NtApplication::initialize(int& argc, char** argv)
{
    m_commandLine = new NtCommandLine(argc, argv);

    NtVirtualHost* localhost = new NtVirtualHost();
    m_virtualHosts.push_back(localhost);

    NtRoute* index = new NtRoute();
    localhost->addRoute(index);

    return onInit();
}

int NtApplication::run()
{
    m_running = true;
    m_httpServer = new NtHTTPServer();

    m_httpServer->initTCPServer("127.0.0.1", 80);

    for (auto& h : m_virtualHosts) {
        m_httpServer->addHost(h);
    }

    while (m_running)
        ;

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

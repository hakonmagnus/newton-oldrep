// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtCommandLine.h
 * \brief Command-line parser
 * \author Hákon Hjaltalín
 *
 * This file contains a command-line parser for Newton applications.
 */

#include "newton/base/NtDefs.h"
#include <string>
#include <vector>
#include <map>

namespace newton
{

/**
 * \class NtCommandLine
 * \brief Command-line parser
 *
 * This class parses and stores command line arguments.
 */
class NT_EXPORT NtCommandLine
{
public:
    /**
     * \brief Constructor
     *
     * Default constructor.
     */
    NtCommandLine() { }
    
    /**
     * \brief Constructor
     *
     * Constructor from command line params.
     *
     * \param argc Argument count
     * \param argv Argument vector
     */
    NtCommandLine(int& argc, char** argv)
    {
        if (argc) {
            parse(argc, argv);
        }
    }

    /**
     * \brief Destructor
     */
    ~NtCommandLine();

    /**
     * \brief Get commands
     *
     * Get commands
     *
     * \return Commands
     */
    std::vector<std::string> commands() const { return m_commands; }

    /**
     * \brief Get arguments
     *
     * Get argument map
     *
     * \return Arguments
     */
    std::map<std::string, std::string> arguments() const { return m_arguments; }

    /**
     * \brief Get argument
     *
     * Get specific argument
     *
     * \param name Argument name
     * \return Argument value
     */
    std::string argument(const std::string& name)
    {
        return m_arguments[name];
    }
    
    /**
     * \brief Parse command line
     *
     * Parse command-line arguments.
     *
     * \param argc Argument count
     * \param argv Argument vector
     */
    void parse(int& argc, char** argv);

private:
    /**
     * \brief List of commands
     */
    std::vector<std::string> m_commands;

    /**
     * \brief Map of arguments
     */
    std::map<std::string, std::string> m_arguments;
};

}


// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtLogger.h
 * \brief Logger class
 * \author Hákon Hjaltalín
 *
 * This file contains the singleton class for the logger.
 */

#include "newton/base/NtDefs.h"
#include <iostream>
#include <string>

namespace newton
{
/**
 * \enum NtLogLevel
 * \brief Level of logging
 *
 * This enum describes the log level.
 */
enum NtLogLevel {
  LOG_TRACE = 0,  ///< Verbatim
  LOG_DEBUG,      ///< Debug
  LOG_INFO,       ///< Information
  LOG_WARN,       ///< Warnings
  LOG_ERROR,      ///< Error
  LOG_FATAL       ///< Fatal error
};

/**
 * \class NtLogger
 * \brief Logger class
 *
 * This is the singleton logger class.
 */
class NT_EXPORT NtLogger
{
  public:
  /**
   * \brief Get logger instance
   *
   * Get the instance of the logger class.
   *
   * \return Logger instance
   */
  static NtLogger* instance();

  /**
   * \brief Set log level
   *
   * Set the current logging level.
   *
   * \param level Log level
   */
  void setLevel(const NtLogLevel level) { m_level = level; }

  /**
   * \brief Log message
   *
   * Output a message to the log.
   *
   * \param msg Message to print
   * \param level Message log level
   */
  void log(const std::string& msg, const NtLogLevel level = LOG_INFO);

  private:
  /**
   * \brief Default constructor
   *
   * Hidden default constructor.
   */
  NtLogger();

  /**
   * Instance
   */
  static NtLogger* m_instance;

  /**
   * Log level
   */
  NtLogLevel m_level;
};

}  // namespace newton

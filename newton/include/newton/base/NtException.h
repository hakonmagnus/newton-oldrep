// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtException.h
 * \brief Newton exception definitions
 * \author Hákon Hjaltalín
 *
 * This file contains various exceptions for the Newton Framework.
 */

#include "newton/base/NtDefs.h"
#include <exception>
#include <string>

namespace newton
{
/**
 * \class NtException
 * \brief Base exception class
 */
class NT_EXPORT NtException : public std::exception
{
  public:
  /**
   * \brief Constructor
   *
   * Default constructor with an error message.
   *
   * \param msg Error message
   */
  NtException(const std::string& msg) : m_message{msg} {}

  /**
   * \brief Virtual destructor
   */
  virtual ~NtException() {}

  /**
   * \brief Exception message
   *
   * Returns the stored error message.
   *
   * \return Error message
   */
  virtual const char* what() const throw() { return m_message.c_str(); }

  protected:
  std::string m_message;
};

/**
 * \class NtInitializeError
 * \brief Initialization exception
 *
 * Exception thrown when initialization fails for some reason
 *
 */
class NT_EXPORT NtInitializeError : public NtException
{
  public:
  /**
   * \brief Default constructor
   *
   * Default constructor with error message.
   *
   * \param msg Error message
   */
  NtInitializeError(const std::string& msg) : NtException{msg}
  {
    m_message = "Initialization error: " + m_message;
  }

  /**
   * \brief Virtual destructor
   */
  virtual ~NtInitializeError() {}
};

/**
 * \class NtNullException
 * \brief Null exception
 *
 * Exception thrown when an argument or other variable is null
 *
 */
class NT_EXPORT NtNullException : public NtException
{
  public:
  /**
   * \brief Default constructor
   *
   * Default constructor with error message.
   *
   * \param msg Error message
   */
  NtNullException(const std::string& msg) : NtException{msg}
  {
    m_message = "Null exception: " + m_message;
  }

  /**
   * \brief Virtual destructor
   */
  virtual ~NtNullException() {}
};

/**
 * \class NtInvalidArgument
 * \brief Invalid argument
 *
 * Exception thrown when an argument is invalid
 *
 */
class NT_EXPORT NtInvalidArgument : public NtException
{
  public:
  /**
   * \brief Default constructor
   *
   * Default constructor with error message.
   *
   * \param msg Error message
   */
  NtInvalidArgument(const std::string& msg) : NtException{msg}
  {
    m_message = "Invalid argument exception: " + m_message;
  }

  /**
   * \brief Virtual destructor
   */
  virtual ~NtInvalidArgument() {}
};
}  // namespace newton

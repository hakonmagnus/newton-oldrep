// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtApplication.h
 * \brief Application class
 *
 * This file contains the definitions for a Newton application.
 */

#include "newton/base/NtCommandLine.h"

namespace newton
{
/**
 * \class NtApplication
 * \brief Application base class
 *
 * This is the base class for a Newton application.
 */
class NT_EXPORT NtApplication
{
  public:
  /**
   * \brief Constructor
   *
   * Default constructor.
   *
   */
  NtApplication();

  /**
   * \brief Destructor
   *
   * Virtual destructor
   */
  virtual ~NtApplication();

  /**
   * \brief Initialize application
   *
   * Initialize the application.
   *
   * \param argc Argument count
   * \param argv Argument vector
   * \return True on success
   */
  bool initialize(int& argc, char** argv);

  /**
   * \brief Run the application
   *
   * Enter the application main loop.
   *
   * \return Exit code
   */
  int run();

  /**
   * \brief Exit application
   *
   * Exit the application with a specified return code.
   *
   * \param code Exit code
   */
  void exit(int code);

  /**
   * \brief Handle on init
   *
   * This function is called upon application initialization.
   *
   * \return True on success
   */
  virtual bool onInit();

  /**
   * \brief Handle on exit
   *
   * This function is called when the application exits.
   */
  virtual void onExit();

  /**
   * \brief Get application instance
   *
   * Get the application's static instance.
   *
   * \return App instance
   */
  static NtApplication* instance() { return ms_instance; }

  private:
  /**
   * Application instance
   */
  static NtApplication* ms_instance;
  
  /**
   * Is running?
   */
  bool m_running;
  
  /**
   * Exit code
   */
  int m_exitCode;

  /**
   * Command-line parser
   */
  NtCommandLine* m_commandLine;
};

}  // namespace newton

/**
 * \def NT_IMPLEMENT_APP
 * \brief Implement application
 *
 * This macro implements the main function for the application
 * and creates a new app instance.
 */
#define NT_IMPLEMENT_APP(apptype)                                              \
  int main(int argc, char** argv)                                              \
  {                                                                            \
    apptype* app = new apptype();                                              \
    if (!app->initialize(argc, argv)) {                                        \
      return -1;                                                               \
    }                                                                          \
    return app->run();                                                         \
  }

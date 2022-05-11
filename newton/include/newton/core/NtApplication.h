// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtApplication.h
 * \brief Base application class
 * \author Hákon Hjaltalín
 *
 * This file contains the application class definition.
 */

#include "newton/base/NtDefs.h"

namespace newton
{
/**
 * \class NtApplication
 * \brief Base application class
 *
 * This is the base class for a Newton application. This class should
 * be derived from to create a custom Newton application.
 */
class NT_EXPORT NtApplication
{
  public:
  /**
   * \brief Default constructor
   */
  NtApplication();

  /**
   * No copy construction
   */
  NtApplication(const NtApplication&) = delete;

  /**
   * No move construction
   */
  NtApplication(NtApplication&&) = delete;

  /**
   * \brief Virtual destructor
   */
  virtual ~NtApplication();

  /**
   * \brief On initialize
   *
   * This function is called when the application is
   * initialized and can be overridden.
   *
   * \param argc Command line argument count
   * \param argv Command line argument vector
   * \return True on success
   */
  virtual bool onInit(int& argc, char** argv);

  /**
   * \brief On exit
   *
   * This function is called when the application exits.
   */
  virtual void onExit();

  /**
   * \brief Run application
   *
   * The main function calls this function to run the
   * application.
   *
   * \return Exit code
   */
  int run();

  /**
   * \brief Get app instance
   *
   * Get the application instance.
   *
   * \return Application instance
   */
  static NtApplication* instance() { return ms_instance; }

  protected:
  /**
   * True if app is running
   */
  bool m_isRunning;

  /**
   * Application instance
   */
  static NtApplication* ms_instance;
};

}  // namespace newton

/**
 * \def NT_IMPLEMENT_APP(apptype)
 * \brief Implement application
 *
 * This macro implements the application main function.
 *
 * \param apptype Application class name
 */
#define NT_IMPLEMENT_APP(apptype)                                              \
  int main(int argc, char** argv)                                              \
  {                                                                            \
    apptype* app = new apptype();                                              \
    if (!app->onInit(argc, argv)) {                                            \
      return -1;                                                               \
    }                                                                          \
    return app->run();                                                         \
  }

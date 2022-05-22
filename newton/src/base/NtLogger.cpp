// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#include "newton/newton.h"
using namespace newton;

#include <iomanip>
#include <ctime>

NtLogger* NtLogger::m_instance{nullptr};

NtLogger::NtLogger() : m_level{LOG_INFO} {}

NtLogger* NtLogger::instance()
{
  if (!m_instance) {
    m_instance = new NtLogger();
  }
  return m_instance;
}

void NtLogger::log(const std::string& msg, const NtLogLevel level)
{
  if (level < m_level) {
    return;
  }

  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);

  switch (level) {
    case LOG_TRACE: {
      std::cout << std::put_time(&tm, "%d-%m-%Y %H:%M:%S");
      std::cout << " [TRACE] ";
    } break;
    case LOG_DEBUG: {
      std::cout << "\033[0;33m" << std::put_time(&tm, "%d-%m-%Y %H:%M:%S");
      std::cout << " [DEBUG] ";
    } break;
    case LOG_INFO: {
      std::cout << "\033[0;34m" << std::put_time(&tm, "%d-%m-%Y %H:%M:%S");
      std::cout << " [INFO]  ";
    } break;
    case LOG_WARN: {
      std::cout << "\033[1;33m" << std::put_time(&tm, "%d-%m-%Y %H:%M:%S");
      std::cout << " [WARN]  ";
    } break;
    case LOG_ERROR: {
      std::cout << "\033[1;31m" << std::put_time(&tm, "%d-%m-%Y %H:%M:%S");
      std::cout << " [ERROR] ";
    } break;
    case LOG_FATAL: {
      std::cout << "\033[7;31m" << std::put_time(&tm, "%d-%m-%Y %H:%M:%S");
      std::cout << " [FATAL] ";
    } break;
  }

  std::cout << msg << "\033[0m" << std::endl;
}

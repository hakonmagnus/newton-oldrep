// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#pragma once

/**
 * \file NtDefs.h
 * \brief Common definitions
 * \author Hákon Hjaltalín
 *
 * This file contains common platform, compiler, and language definitions.
 */

#ifndef __cplusplus
#  error A C++ compielr must be used to build Newton.
#else
#  if ((defined(_MSVC_LANG) && _MSVC_LANG < 201402L) || __cplusplus < 201402L)
#    error Your compiler must support C++14 or higher.
#  endif
#endif

#if (defined(DEBUG) || defined(_DEBUG)) && !defined(NDEBUG)
#  define NT_DEBUG
#else
#  ifdef NT_DEBUG
#    undef NT_DEBUG
#  endif
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#  define NT_WINDOWS
#elif defined(__APPLE__) || defined(__MACH__)
#  define NT_APPLE
#elif defined(unix) || defined(__unix) || defined(__unix__)
#  define NT_UNIX
#else
#  error Unsupported platform.
#endif

#if defined(__INTEL_COMPILER) || defined(__ICC)
#  define NT_COMPILER_INTEL
#elif defined(__BORLANDC__)
#  define NT_COMPILER_BORLANDC
#elif defined(__clang__)
#  define NT_COMPILER_CLANG
#  if defined(__apple_build_version__)
#    define NT_APPLE_CLANG
#  endif
#elif defined(__GNUC__)
#  define NT_COMPILER_GCC
#elif defined(_MSC_VER)
#  define NT_COMPILER_MSVC
#else
#  define NT_COMPILER_UNKNOWN
#endif

#if defined(NT_APPLE_CLANG)
#  if !(((__clang_major__ * 100) + __clang_minor__) >= 510)
#    error Unsupported compiler.
#  endif
#  define NT_COMPILER_VERSION_MAJOR (__clang_major__)
#  define NT_COMPILER_VERSION_MINOR (__clang_minor__)
#  define NT_COMPILER_VERSION_PATCH (__clang_patchlevel__)
#  if defined(_MSC_VER)
#    define NT_SIMULATE_VERSION_MAJOR (_MSC_VER / 100)
#    define NT_SIMULATE_VERSION_MINOR (_MSC_VER % 100)
#  endif
#elif defined(NT_COMPILER_CLANG)
#  if !(((__clang_major__ * 100) + __clang_minor__) > 340)
#    error Unsupported compiler.
#  endif
#  define NT_COMPILER_VERSION_MAJOR (__clang_major__)
#  define NT_COMPILER_VERSION_MINOR (__clang_minor__)
#  define NT_COMPILER_VERSION_PATCH (__clang_patchlevel__)
#  if defined(_MSC_VER)
#    define NT_SIMULATE_VERSION_MAJOR (_MSC_VER / 100)
#    define NT_SIMULATE_VERSION_MINOR (_MSC_VER % 100)
#  endif
#elif defined(NT_COMPILER_GCC)
#  if !((__GNUC__ * 100 + __GNUC_MINOR__) >= 500)
#    error Unsupported compiler.
#  endif
#  define NT_COMPILER_VERSION_MAJOR (__GNUC__)
#  define NT_COMPILER_VERSION_MINOR (__GNUC_MINOR__)
#  if defined(__GNUC_PATCHLEVEL__)
#    define NT_COMPILER_VERSION_PATCH (__GNUC_PATCHLEVEL__)
#  endif
#elif defined(NT_COMPILER_MSVC)
#  if !(_MSC_VER >= 1900)
#    error Unsupported compiler.
#  endif
#  define NT_COMPILER_VERSION_MAJOR (_MSC_VER / 100)
#  define NT_COMPILER_VERSION_MINOR (_MSC_VER % 100)
#  if defined(_MSC_FULL_VER)
#    define NT_COMPILER_VERSION_PATCH (_MSC_FULL_VER % 100000)
#  endif
#else
#  error Unsupported compiler·
#endif

#ifndef NT_EXPORT
#  if defined(NT_WINDOWS) && defined(NT_COMPILER_MSVC) && defined(NT_SHARED_LIBS)
#    define NT_EXPORT __declspec(dllexport)
#  else
#    define NT_EXPORT
#  endif
#endif

#ifndef NT_IMPORT
#  if defined(NT_WINDOWS) && defined(NT_COMPILER_MSVC) && defined(NT_SHARED_LIBS)
#    define NT_IMPORT extern __declspec(dllimport)
#  else
#    define NT_IMPORT extern
#  endif
#endif

#if defined(NT_WINDOWS)
#  ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN
#  endif
#  ifndef NOGDI
#    define NOGDI
#  endif
#  ifndef NOKERNEL
#    define NOKERNEL
#  endif
#  ifndef NOUSER
#    define NOUSER
#  endif
#  ifndef NONLS
#    define NONLS
#  endif
#  ifndef NOMB
#    define NOMB
#  endif
#  ifndef NOMINMAX
#    define NOMINMAX
#  endif
#  ifndef NOSOUND
#    define NOSOUND
#  endif
#  ifndef NOCOMM
#    define NOCOMM
#  endif
#  ifndef NOHELP
#    define NOHELP
#  endif
#  ifndef NOPROFILER
#    define NOPROFILER
#  endif
#  ifndef NODEFERWINDOWPOS
#    define NODEFERWINDOWPOS
#  endif
#  ifndef NOMETAFILE
#    define NOMETAFILE
#  endif
#  ifndef NOSCROLL
#    define NOSCROLL
#  endif
#  ifndef NORASTEROPS
#    define NORASTEROPS
#  endif
#  ifndef NOATOM
#    define NOATOM
#  endif
#  include <windows.h>
#endif

#include <cstdint>
#include <cstddef>

using std::max_align_t;
using std::ptrdiff_t;
using std::size_t;

using std::int16_t;
using std::int32_t;
using std::int64_t;
using std::int8_t;

using std::int_fast16_t;
using std::int_fast32_t;
using std::int_fast64_t;
using std::int_fast8_t;

using std::int_least16_t;
using std::int_least32_t;
using std::int_least64_t;
using std::int_least8_t;

using std::intmax_t;
using std::intptr_t;

using std::uint16_t;
using std::uint32_t;
using std::uint64_t;
using std::uint8_t;

using std::uint_fast16_t;
using std::uint_fast32_t;
using std::uint_fast64_t;
using std::uint_fast8_t;

using std::uint_least16_t;
using std::uint_least32_t;
using std::uint_least64_t;
using std::uint_least8_t;

using std::uintmax_t;
using std::uintptr_t;

#if defined(NT_WINDOWS)
#  include <winsock2.h>
#  include <ws2tcpip.h>
#  if NT_COMPILER_MSVC
#    pragma comment(lib, "Ws2_32.lib")
#  endif
#else
#  include <sys/types.h>
#  include <sys/socket.h>
#  include <netinet/in.h>
#endif

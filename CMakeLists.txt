cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

include(cmake/Custom.cmake)

set_policy(CMP0048 NEW) # OK to clear PROJECT_VERSION on project()
set_policy(CMP0054 NEW) # Only interpret if() arguments as variables or keywords when unquoted
set_policy(CMP0056 NEW) # export EXE_LINKER_FLAGS to try_run
set_policy(CMP0057 NEW) # Support no if() IN_LIST operator
set_policy(CMP0063 NEW) # Honor visibility properties for all targets
set_policy(CMP0077 NEW) # Allow option() overrides in importing projects

# Module directory
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Disable in-source build
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

# Project
project(newton
    VERSION 1.0.0
    LANGUAGES C CXX
)

# CXX Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Default build type
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose: Debug, Release, RelWithDebInfo, MinSizeRel, Coverage." FORCE)
endif ()

# Common includes
include(Options)
include(CompilerOptions)

# IDE folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Build system info
include(PrintInfo)

# Configuration
if (BUILD_SHARED_LIBS)
    set(NT_HEADER_SHARED_LIBS "#define NT_SHARED_LIBS")
else ()
    set(NT_HEADER_SHARED_LIBS "")
endif ()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config/config.h.in ${CMAKE_BINARY_DIR}/config/config.h @ONLY)

# Subdirectories
add_subdirectory(newton)

if (NT_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()

if (NT_BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif ()

# Tools and analyzers
include(Cppcheck)
include(ClangTools)

# Testing
if (NT_BUILD_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
endif ()

# Documentation
if (NT_BUILD_DOCS)
    find_package(Doxygen)

    if (DOXYGEN_FOUND)
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

        add_custom_target(doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
    else ()
        message(WARNING "Doxygen needs to be installed to generate the Doxygen documentation.")
    endif ()
endif ()

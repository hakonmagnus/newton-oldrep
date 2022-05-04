// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

/**
 * \file main.cpp
 * \brief Main unit testing file
 * \author Hákon Hjaltalín
 *
 * This is the main source file for the unit tests.
 */

#include "gtest/gtest.h"

using ::testing::InitGoogleTest;
using ::testing::Test;

int main(int argc, char** argv) {
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

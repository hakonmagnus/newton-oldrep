// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#include "gtest/gtest.h"
#include "newton/newton.h"
using namespace newton;

TEST(NtJSONTest, String)
{
    NtJSONString str("Hello");
    EXPECT_EQ("Hello", str.value());
    str.setValue("test");
    EXPECT_EQ("test", str.value());
}

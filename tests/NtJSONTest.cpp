// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#include "gtest/gtest.h"
#include "newton/newton.h"
using namespace newton;

TEST(NtJSONTest, String)
{
    NtJSONString str("hello");
    EXPECT_EQ("hello", str.value());
    str.setValue("world");
    EXPECT_EQ("world", str.value());
    str.fromNumber(4.5);
    EXPECT_EQ("4.5", str.value());
    EXPECT_EQ(4.5, str.toNumber());
    str = "test";
    EXPECT_EQ(true, str == "test");
    NtJSONString str2("test");
    EXPECT_EQ(true, str == str2);
}

TEST(NtJSONTest, Number)
{
    NtJSONNumber num(4.5);
    EXPECT_DOUBLE_EQ(4.5, num.value());
    num.setValue(1.2);
    EXPECT_DOUBLE_EQ(1.2, num.value());
    num.fromString("8.2");
    EXPECT_DOUBLE_EQ(8.2, num.value());
    EXPECT_EQ("8.2", num.toString());
    num = 5.0;
    EXPECT_EQ(true, num == 5.0);
    NtJSONNumber num2(5.0);
    EXPECT_EQ(true, num == num2);
}

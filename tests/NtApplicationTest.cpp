// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#include "gtest/gtest.h"
#include "newton/newton.h"
using namespace newton;

class MyApp : public NtApplication
{
public:
};

TEST(NtApplicationTest, Instance)
{
    MyApp* ma = new MyApp();
    EXPECT_EQ(ma, ma->instance());
    delete ma;
    ma = nullptr;
}


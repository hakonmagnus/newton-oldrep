// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#include "newton/newton.h"
using namespace newton;

#include <fstream>

class MyApp : public NtApplication
{
  public:
  MyApp() : NtApplication() {}

  virtual bool onInit() override
  {
    return true;
  }
};

NT_IMPLEMENT_APP(MyApp)

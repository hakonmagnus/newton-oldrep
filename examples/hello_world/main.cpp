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
    char* json = nullptr;
    std::ifstream file("test.json", std::ios::in);
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);
    json = new char[size + 1];
    file.read(json, size);
    file.close();

    try {
        auto obj = NtParseJSON(json);
        NtJSONElement* e1 = obj->get("quiz");
        NtJSONObject* o1 = (NtJSONObject*)e1;

        std::cout << o1->count() << std::endl;
    } catch (NtException& e) {
        std::cerr << "Exception: " << e.message() << std::endl;
    }
  }
};

NT_IMPLEMENT_APP(MyApp)

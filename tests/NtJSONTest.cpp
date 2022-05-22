// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#include "gtest/gtest.h"
#include "newton/newton.h"
using namespace newton;

#include <fstream>

TEST(NtJSONTest, NtJSONObject)
{
    NtJSONObject* obj = new NtJSONObject();
    NtJSONString* s1 = new NtJSONString("one");
    NtJSONString* s2 = new NtJSONString("two");
    obj->add("s1", s1);
    obj->add("s2", s2);

    EXPECT_EQ(true, ((NtJSONString*)obj->get("s1"))->value() == "one");

    delete s1;
    s1 = nullptr;
    delete s2;
    s2 = nullptr;
    delete obj;
    obj = nullptr;
}

TEST(NtJSONTest, NtJSONArray)
{
    NtJSONArray* arr = new NtJSONArray();
    NtJSONString* s1 = new NtJSONString("one");
    NtJSONString* s2 = new NtJSONString("two");
    arr->add(s1);
    arr->add(s2);

    EXPECT_EQ(true, ((NtJSONString*)(*arr)[0])->value() == "one");
    EXPECT_EQ(true, ((NtJSONString*)(*arr)[1])->value() == "two");

    delete s1;
    s1 = nullptr;
    delete s2;
    s2 = nullptr;
    delete arr;
    arr = nullptr;
}

TEST(NtJSONTest, NtJSONString)
{
    NtJSONString* str = new NtJSONString("5");
    EXPECT_EQ(true, str->value() == "5");
    EXPECT_EQ(5, str->toNumber());
    str->setValue(20);
    EXPECT_EQ(20, str->toNumber());
    delete str;
    str = nullptr;
}

TEST(NtJSONTest, NtJSONNumber)
{
    NtJSONNumber* num = new NtJSONNumber("5");
    EXPECT_DOUBLE_EQ(5, num->value());
    num->setValue(22.3);
    EXPECT_DOUBLE_EQ(22.3, num->value());
    delete num;
    num = nullptr;
}

TEST(NtJSONTest, NtJSONBoolean)
{
    NtJSONBoolean* b = new NtJSONBoolean("true");
    EXPECT_EQ(true, b->value());
    b->setValue(3);
    EXPECT_EQ(true, b->value());
    b->setValue(0);
    EXPECT_EQ(false, b->value());
    delete b;
    b = nullptr;
}

TEST(NtJSONTest, NtJSONParse)
{
    std::ifstream file("test.json", std::ios::in);
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);

    char* buf = new char[size + 1];
    file.read(buf, size);
    file.close();

    NtJSONObject* obj = NtParseJSON(buf);
    EXPECT_EQ(1, obj->count());

    NtJSONElement* e1 = obj->get("quiz");
    EXPECT_EQ(true, e1 != nullptr);
    EXPECT_EQ(NtJSONElement::Type::OBJECT, e1->type());
    
    NtJSONObject* o1 = static_cast<NtJSONObject*>(e1);
    EXPECT_EQ(2, o1->count());

    NtJSONElement* e2 = o1->get("sport");
    EXPECT_EQ(true, e2 != nullptr);
    EXPECT_EQ(NtJSONElement::Type::OBJECT, e2->type());

    NtJSONObject* o2 = static_cast<NtJSONObject*>(e2);
    EXPECT_EQ(1, o2->count());

    NtJSONElement* e3 = o2->get("q1");
    EXPECT_EQ(true, e3 != nullptr);
    EXPECT_EQ(NtJSONElement::Type::OBJECT, e3->type());

    NtJSONObject* o3 = static_cast<NtJSONObject*>(e3);
    EXPECT_EQ(3, o3->count());

    NtJSONElement* e4 = o3->get("options");
    EXPECT_EQ(true, e4 != nullptr);
    EXPECT_EQ(NtJSONElement::Type::ARRAY, e4->type());

    NtJSONArray* a1 = static_cast<NtJSONArray*>(e4);
    EXPECT_EQ(4, a1->count());
    
    NtJSONElement* e5 = a1->get(1);
    EXPECT_EQ(true, e5 != nullptr);
    EXPECT_EQ(NtJSONElement::Type::STRING, e5->type());
    
    NtJSONString* str = static_cast<NtJSONString*>(e5);
    EXPECT_EQ(true, str->value() == "Los Angeles Kings");
    
    delete buf;
    buf = nullptr;
}

# Newton Framework Coding Standards

This document describes the C/C++ coding standards and style guidelines imposed on all
source code produced for the Newton Framework and related projects.

## Core Guidelines

Please follow the [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) in your code.

## Formatting

Please take a look at the [.clang-format](./.clang-format) configuration file to see how the formatting tool is set up.

## C++ Version

Compilers must always support C++17 or later, and code can be written under the assumption
that C++17 features are supported. If a compiler is used which does not support C++17, an error
must be thrown during the compilation process.

## File Extensions

Header files have a `.h` extension regardless of whether the language in question is C or C++.
C++ source files have a `.cpp` extension. C files have a `.c` extension.

## Header guards

Header files should use a pragma definition at the top as follows:

```c++
#pragma once

...
```
## Include files ordering

Use the following order for including headers:

1. Generated headers (config.h)
2. Related headers
3. External library headers
4. C system headers
5. C++ standard library headers

## Naming conventions

The following sections describe identifier naming conventions throughout the code.

### Naming Macros

Pre-processor macros use all uppercase letters and underscores.

```c++
#define MY_MACRO
```

### Naming Namespaces

Namespace names should use all lowercase.

```c++
namespace mynamespace {

}
```

### Naming Classes

Class names use capitalizations on each word and starts with a capital letter.

```c++
class MyClass {

};
```

### Naming Files

File names may have an Nt prefix. Additionally, word capitalization is generally used:

```
NtMyFile.h
config.h
SomeHeaderNoPrefix.h
NtAPIClassAcronyms.h
NtAPIClassAcronyms.cpp
```

These naming conventions are only loosely defined for our purposes.

### Naming Variables

Variables use camelCase:

```c++
myVariableName
```

Private class members use an `m_` prefix:

```c++
class MyClass {
private:
    int m_privateMember;
};
```

Static variables use an `s_` prefix:

```c++
static int s_myVar;

class MyClass {
private:
    static int ms_staticMember;
};
```

Global variables use a `g_` prefix:

```c++
int g_myGlobal;
```

Boolean variables and class members should have an `is`, `has`, or other relevant prefix as follows:

```c++
class Application {
protected:
    int m_isRunning;
};
```

### Naming Functions

Standalone functions use camelCase with a lowercase letter at the start:

```c++
int myFunction();
```

#### Getters and Setters

Getter functions use the exact same name as the variable. Setter functions have a `set` prefix as follows:

```c++
class NtRectangle {
public:
    int x() const;

    void setX(const int x);
};
```

## Enum Names

Enum names follow the same conventions as class names:

```c++
enum class MyEnum {
...
};
```

## File Headers

The following comment should appear at the top of each C/C++ source file:

```c++
//
// Copyright (c) 2022 Hákon Hjaltalín
//
// This project is licensed under the MIT License. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.
//
```

## Doxygen

A Doxygen comment block should be formatted like this:

```c++
/**
 * \brief Some brief description
 *
 * Longer description, other commands
 *
 */
```


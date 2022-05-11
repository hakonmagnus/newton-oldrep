<div align="center">
  <a href="https://newtonframework.com">
    <img width="200" height="200" src="https://github.com/hakonmagnus/newton/blob/master/docs/newton.svg">
  </a>
  <br>
  <br>

![GitHub](https://img.shields.io/github/license/hakonmagnus/newton)
![Lines of code](https://img.shields.io/tokei/lines/github/hakonmagnus/newton.git)
[![Build Status](https://app.travis-ci.com/hakonmagnus/newton.svg?branch=master)](https://app.travis-ci.com/hakonmagnus/newton)
[![codecov](https://codecov.io/gh/hakonmagnus/newton/branch/main/graph/badge.svg?token=Q4D0VVZO10)](https://codecov.io/gh/hakonmagnus/newton)
[![Build status](https://ci.appveyor.com/api/projects/status/tmmgc9107v4xagat/branch/master?svg=true)](https://ci.appveyor.com/project/hakonmagnus/newton/branch/master)

  <br>
  <h1>Newton</h1>
  <p>
    Newton is a C++ web framework allowing you to create web applications in the C++ language.
  </p>
</div>

## Table of Contents

1. [Introduction](#introduction)
2. [Install](#install)
3. [Usage](#usage)
4. [Contributing](#contributing)
5. [License](#license)

<h2 align="center">Introduction</h2>

Newton is a C++ web framework for creating compiled, custom web servers. This framework allows
you to unleash the speed of C++ and you are at an advantage when you are able to compile your
server rather than use an interpreter.

<h2 align="center">Install</h2>

To build and install Newton, you will need CMake and a C++17-capable compiler. Clone the repository
and create your build directory:

```sh
git clone https://github.com/hakonmagnus/newton.git
cd newton
git submodule update --init --recursive
mkdir build
cd build
```

Now you can build the project using CMake, and then install:

```sh
cmake ..
make
make install
```

<h2 align="center">Usage</h2>

Please see the [Newton Documentation](https://newtonframework.com) for examples and documentation.

<h2 align="center">Contributing</h2>

Please see [CONTRIBUTING.md](./CONTRIBUTING.md) for information about how to contribute to Newton.

<h2 align="center">License</h2>

This project is licensed under the [MIT Liccense](./LICENSE).


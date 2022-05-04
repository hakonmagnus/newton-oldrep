if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Weverything)
endif ()

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if (NT_WARNINGS_AS_ERRORS)
        add_compiile_options(-Werror)
    endif ()

    add_compile_options(-pedantic)
    add_compile_options(-Wall)
    add_compile_options(-Wextra)
endif ()

if (CMAKE_BUILD_TYPE MATCHES "Coverage")
    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        add_compile_options(-g0)
        add_compile_options(-O0)
        add_compile_options(-fprofile-arcs)
        add_compile_options(-ftest-coverage)
    else ()
        message(FATAL_ERROR "The GNU gcc compiler must be used during coverage builds.")
    endif ()
endif ()

if (MSVC)
    if (MSVC_VERSION LESS 1911)
        message(FATAL_ERROR "Visual Studio 2017 version 15.3 or later must be used.")
    endif ()

    add_compile_options(/W4)
    add_compile_options(/Zi)

    if (NT_WARNINGS_AS_ERRORS)
        add_compile_options(/WX)
    endif ()
    add_compile_options(/MP)

    if (CMAKE_BUILD_TYPE MATCHES "Release" OR CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo")
        add_compile_options(/O2)
        add_compile_options(/Ob2)
        add_compile_options(/Oi)
        add_compile_options(/Ot)
        add_compile_options(/Oy)
        add_compile_options(/GS-)
        add_compile_options(/Gy)
        add_compile_options(/GF)
        add_compile_options(/MD)
    else ()
        add_compile_options(/Od)
        add_compile_options(/GS)
        add_compile_options(/MDd)
    endif ()

    add_compile_options(/std:c++17)

    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        add_link_options(/INCREMENTAL)
    endif ()
endif ()

set(NEWTON_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/base/NtObject.cpp
)

set(NEWTON_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newton/newton.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newton/base/NtDefs.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newton/base/NtObject.h
)

if (BUILD_SHARED_LIBS)
    add_library(newton SHARED ${NEWTON_SOURCES} ${NEWTON_HEADERS})
else ()
    add_library(newton STATIC ${NEWTON_SOURCES} ${NEWTON_HEADERS})
endif ()

# Directories and libraries

target_include_directories(newton PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/config
)

# Options

set_target_properties(newton PROPERTIES FOLDER "")

# Lists

set(NT_SOURCE_FILES ${NT_SOURCE_FILES} ${NEWTON_SOURCES} PARENT_SCOPE)
set(NT_INCLUDE_FILES ${NT_INCLUDE_FILES} ${NEWTON_INCLUDES} PARENT_SCOPE)

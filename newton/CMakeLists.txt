set(NEWTON_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/NtApplication.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/NtHTTPServer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/NtVirtualHost.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/NtRoute.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/base/NtLogger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/base/NtCommandLine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/json/NtJSONParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/http/NtHTTPRequest.cpp
)

set(NEWTON_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newton/newton.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newton/base/NtDefs.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newton/base/NtLogger.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newton/base/NtCommandLine.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newton/core/NtApplication.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newton/core/NtServer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newton/core/NtHTTPServer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newton/core/NtVirtualHost.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newton/core/NtRoute.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newton/json/NtJSONElement.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newton/json/NtJSONObject.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newton/json/NtJSONArray.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newton/json/NtJSONString.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newton/json/NtJSONNumber.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newton/json/NtJSONBoolean.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newton/json/NtJSONNull.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newton/json/NtJSONParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newton/string/NtString.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newton/http/NtHTTPHeader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newton/http/NtHTTPMessage.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newton/http/NtHTTPRequest.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newton/dom/NtDocument.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newton/html/NtHTMLParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/newton/ncl/NtNCLToken.h
)

if (WIN32)
    set(NEWTON_SOURCES ${NEWTON_SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/src/core/NtServerWin.cpp)
else ()
    set(NEWTON_SOURCES ${NEWTON_SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/src/core/NtServerUNIX.cpp)
endif ()

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

if (UNIX)
    target_link_libraries(newton pthread)
endif ()

# Options

set_target_properties(newton PROPERTIES FOLDER "")

# Lists

set(NT_SOURCE_FILES ${NT_SOURCE_FILES} ${NEWTON_SOURCES} PARENT_SCOPE)
set(NT_INCLUDE_FILES ${NT_INCLUDE_FILES} ${NEWTON_INCLUDES} PARENT_SCOPE)


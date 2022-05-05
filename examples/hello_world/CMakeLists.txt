set(HELLO_WORLD_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_executable(hello_world ${HELLO_WORLD_SOURCES})

# Directories and libraries

target_link_libraries(hello_world newton)

# Options

set_target_properties(hello_world PROPERTIES FOLDER "examples")

# Lists

set(NT_SOURCE_FILES ${NT_SOURCE_FILES} ${HELLO_WORLD_SOURCES} PARENT_SCOPE)

find_program(CPPCHECK cppcheck)
if (CPPCHECK)
    add_custom_target(
        cppcheck
        COMMAND ${CPPCHECK}
        --quiet
        --error-exitcode=1
        --enable=warning,portability,performance,style
        --std=c++17
        ${NT_SOURCE_FILES}
        ${NT_INCLUDE_FILES}
    )
endif ()

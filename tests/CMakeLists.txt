add_subdirectory("${CMAKE_SOURCE_DIR}/extern/googletest" "extern/googletest")

mark_as_advanced(
    BUILD_GMOCK BUILD_GTEST
    gmock_build_tests gtest_build_samples gtest_build_tests
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

set_target_properties(gtest PROPERTIES FOLDER extern)
set_target_properties(gtest_main PROPERTIES FOLDER extern)
set_target_properties(gmock PROPERTIES FOLDER extern)
set_target_properties(gmock_main PROPERTIES FOLDER extern)

set(TESTS_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_executable(tests ${TESTS_SOURCES})
target_link_libraries(tests gtest gmock gtest_main)
gtest_discover_tests(tests
    WORKING_DIRECTORY ${PROJECT_DIR}
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
)
set_target_properties(tests PROPERTIES FOLDER tests)

if (CMAKE_BUILD_TYPE MATCHES "Coverage")
    include(CodeCoverage)
    setup_target_for_coverage(coverage tests coverage)
    set(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    set(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
endif ()

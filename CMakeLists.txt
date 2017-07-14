cmake_minimum_required(VERSION 3.0)

set(CMAKE_C_COMPILER   "gcc-7")
set(CMAKE_CXX_COMPILER "g++-7")

project(Pie)

find_package(PythonLibs 3.6 REQUIRED)
include(external_googletest.cmake)

set(CMAKE_CXX_FLAGS "-Wall -Werror -g -O3 -std=c++1z")

set(PIE_TEST_DIR "test")
set(PIE_SOURCE_DIR "src")

set(PIE_HEADER_FILES
    "${PIE_SOURCE_DIR}/pie/parse.inl"
    "${PIE_SOURCE_DIR}/pie/parse.h"
    "${PIE_SOURCE_DIR}/pie/object.h"
    "${PIE_SOURCE_DIR}/pie/object.inl"
)

set(PIE_SOURCE_FILES
    "${PIE_SOURCE_DIR}/pie/object.cc"
)

set(PIE_TEST_FILES
    "${PIE_TEST_DIR}/test_parse.cc"
    "${PIE_TEST_DIR}/test_object.cc"
    "${PIE_TEST_DIR}/test_setup.cc"
)

include_directories(
    ${PIE_SOURCE_DIR}
    ${PYTHON_INCLUDE_DIRS}
    ${GTEST_INCLUDE_DIRS}
)

add_library(pie SHARED ${PIE_SOURCE_FILES})
target_link_libraries(pie ${PYTHON_LIBRARY})
add_executable(tests ${PIE_TEST_FILES}) 

target_link_libraries(tests pie ${GTEST_BOTH_LIBRARIES})

add_custom_target(run-tests DEPENDS tests)
add_custom_command(COMMAND ./tests TARGET run-tests)

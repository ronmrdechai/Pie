cmake_minimum_required(VERSION 3.0)

set(CMAKE_C_COMPILER   "gcc-7")
set(CMAKE_CXX_COMPILER "g++-7")

project(Pie)

find_package(PythonLibs 3.6 REQUIRED)

set(CMAKE_CXX_FLAGS "-Wall -Werror -g -O3 -std=c++1z")

set(PIE_TEST_DIR "test")
set(PIE_SOURCE_DIR "src")
set(PIE_EXTERNAL_DIR "ext")

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/${PIE_EXTERNAL_DIR}")
    message(FATAL_ERROR "${PROJECT_SOURCE_DIR}/${PIE_EXTERNAL_DIR} directory \
missing, this directory should contain the newest `catch.hpp' file")
endif()

set(PIE_HEADER_FILES
    "${PIE_SOURCE_DIR}/pie/parse.inl"
    "${PIE_SOURCE_DIR}/pie/parse.h"
    "${PIE_SOURCE_DIR}/pie/python_object.h"
    "${PIE_SOURCE_DIR}/pie/python_object.inl"
)

set(PIE_SOURCE_FILES
    "${PIE_SOURCE_DIR}/pie/python_object.cc"
)

set(PIE_TEST_FILES
    "${PIE_TEST_DIR}/test_main.cc"
    "${PIE_TEST_DIR}/test_parse.cc"
)

include_directories(
    ${PIE_SOURCE_DIR}
    ${PIE_EXTERNAL_DIR}
    ${PYTHON_INCLUDE_DIRS}
)
add_library(pie SHARED ${PIE_SOURCE_FILES})
add_executable(catch ${PIE_TEST_FILES})
target_link_libraries(catch pie ${PYTHON_LIBRARY})

add_custom_target(run-tests)
add_custom_command(COMMAND ./catch DEPENDS catch TARGET run-tests)

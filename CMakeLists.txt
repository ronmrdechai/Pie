cmake_minimum_required(VERSION 3.0)

set(CMAKE_C_COMPILER   "gcc-7")
set(CMAKE_CXX_COMPILER "g++-7")
set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS        NO)

set(CMAKE_BUILD_TYPE        Release)
set(CMAKE_CXX_FLAGS         "-Wall -Werror")
set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

project(Pie)

find_package(PythonLibs 3 REQUIRED)

set(PIE_TEST_DIR "test")
set(PIE_SOURCE_DIR "src")

set(PIE_HEADER_FILES
    "${PIE_SOURCE_DIR}/pie/parse.inl"
    "${PIE_SOURCE_DIR}/pie/parse.h"
    "${PIE_SOURCE_DIR}/pie/object.h"
    "${PIE_SOURCE_DIR}/pie/object.inl"
    "${PIE_SOURCE_DIR}/pie/error.h"
    "${PIE_SOURCE_DIR}/pie/iterator.h"
)

set(PIE_SOURCE_FILES
    "${PIE_SOURCE_DIR}/pie/object.cc"
    "${PIE_SOURCE_DIR}/pie/error.cc"
    "${PIE_SOURCE_DIR}/pie/iterator.cc"
)

include_directories(
    ${PIE_SOURCE_DIR}
    ${PYTHON_INCLUDE_DIRS}
)

add_library(pie SHARED ${PIE_SOURCE_FILES})
target_link_libraries(pie ${PYTHON_LIBRARY})

install(
    TARGETS pie
    DESTINATION "lib"
)
install(
    FILES ${PIE_HEADER_FILES}
    DESTINATION "include"
)

if(${BUILD_TESTS})
    set(PIE_TEST_FILES
        "${PIE_TEST_DIR}/test_parse.cc"
        "${PIE_TEST_DIR}/test_object.cc"
        "${PIE_TEST_DIR}/test_error.cc"
        "${PIE_TEST_DIR}/test_setup.cc"
    )

    include(external_googletest.cmake)

    include_directories(${GTEST_INCLUDE_DIRS})

    add_executable(tests ${PIE_TEST_FILES})
    target_link_libraries(tests pie ${GTEST_BOTH_LIBRARIES})

    enable_testing()
    add_test(NAME tests COMMAND tests)
endif()

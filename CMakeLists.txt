#
# Created by Kyrylo Rud on 05.05.2025.
#

cmake_minimum_required(VERSION 3.24)

project(erelic VERSION 0.0.1
   DESCRIPTION "A minimalist emulator for vintage CPU."
   LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_TESTS "Build and run unit tests" ON)

include(cmake/add_test_executable.cmake)
include(cmake/clang_tools.cmake)
if(ENABLE_TESTS)
   enable_testing()

   find_package(GTest REQUIRED)
   include(GoogleTest)
endif()

add_compile_options(
   -Wall
   -Wextra
   -Wpedantic
   -Werror
)

clang_format(DIRECTORY src/ FILES_REGEX "*.cpp" "*.hpp")
clang_tidy(DIRECTORY src/)

add_subdirectory(src)

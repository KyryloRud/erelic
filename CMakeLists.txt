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

option(ENABLE_TESTS "Build and run unit tests" ON)

include(cmake/add_test_executable.cmake)
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

file(GLOB_RECURSE ALL_SOURCE_FILES CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp")
add_custom_target(format COMMAND clang-format -i ${ALL_SOURCE_FILES} COMMENT "Reformat all source files")
add_custom_target(format-check COMMAND clang-format --dry-run --Werror ${ALL_SOURCE_FILES} COMMENT "Verify source files are clang‑format compliant")

add_subdirectory(src)

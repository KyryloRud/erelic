#
# Created by Kyrylo Rud on 05.05.2025.
#

if(NOT ENABLE_TESTS)
   return()
endif()

set(TARGET core-tests)

add_executable(${TARGET} instruction.cpp address.cpp)
target_link_libraries(${TARGET} PUBLIC gtest gtest_main erelic-core)
gtest_discover_tests(${TARGET})

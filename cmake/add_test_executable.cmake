#
# Created by Kyrylo Rud on 09.05.2025.
#

macro(add_test_executable test_target_name testing_target_name)
  if(ENABLE_TESTS)
    set(TARGET ${test_target_name}-gtest)
    add_executable(${TARGET} ${ARGN})
    target_link_libraries(${TARGET} PUBLIC gtest gtest_main ${testing_target_name})
    gtest_discover_tests(${TARGET})
  endif()
endmacro()

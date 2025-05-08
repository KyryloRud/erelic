#
# Created by Kyrylo Rud on 05.05.2025.
#

set(TARGET erelic-core)

add_library(${TARGET} STATIC
   instruction.hpp
   instruction.cpp
   utility.hpp
   utility.cpp
   address.hpp
   address.cpp
)
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(tests)

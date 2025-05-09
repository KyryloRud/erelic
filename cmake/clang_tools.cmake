#
# Created by Kyrylo Rud on 09.05.2025.
#

find_program(CLANG_FORMAT_EXE NAMES clang-format REQUIRED)
find_program(CLANG_TIDY_EXE NAMES clang-tidy REQUIRED)
find_program(RUN_CLANG_TIDY_EXE NAMES run-clang-tidy REQUIRED)

# Adds a targets to format source files using clang-format.
# Usage: clang_format(DIRECTORY "/path/to/sources" FILES_REGEX "*.cpp" "*.hpp")
# Assumes .clang-format is in the same dir as the CMakeLists.txt where this is called.
function(clang_format)
   set(ONE_VALUE_ARGS DIRECTORY)
   set(MULTI_VALUE_ARGS FILES_REGEX)

   cmake_parse_arguments(PARSE_ARGV 0 ARG "" "${ONE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}")

   if(NOT ARG_DIRECTORY)
      message(FATAL_ERROR "clang_format: DIRECTORY argument is required")
   endif()

   if(NOT ARG_FILES_REGEX)
      message(FATAL_ERROR "clang_format: FILES_REGEX must have at least one glob pattern")
   endif()

   set(ALL_SOURCE_FILES)
   foreach(pattern IN LISTS ARG_FILES_REGEX)
      file(GLOB_RECURSE FILES CONFIGURE_DEPENDS "${ARG_DIRECTORY}/${pattern}")
      list(APPEND ALL_SOURCE_FILES ${FILES})
   endforeach()

   add_custom_target(format COMMAND ${CLANG_FORMAT_EXE} -i ${ALL_SOURCE_FILES} COMMENT "Reformat source files")
   add_custom_target(format-check COMMAND ${CLANG_FORMAT_EXE} --dry-run --Werror ${ALL_SOURCE_FILES} COMMENT "Verify source files are clang‑format compliant")
endfunction()

# Adds a targets to analyze source files using clang-tidy.
# Usage: clang_tidy(DIRECTORY "/path/to/sources")
# Assumes .clang-tidy is in the same dir as the CMakeLists.txt where this is called.
function(clang_tidy)
   set(ONE_VALUE_ARGS DIRECTORY)

   cmake_parse_arguments(ARG "" "${ONE_VALUE_ARGS}" "" ${ARGN})

   if(NOT ARG_DIRECTORY)
      message(FATAL_ERROR "clang_tidy: DIRECTORY argument is required")
   endif()

   if(NOT CMAKE_EXPORT_COMPILE_COMMANDS)
      message(WARNING "CMAKE_EXPORT_COMPILE_COMMANDS is OFF, clang-tidy result are not optimal")
   endif()

   add_custom_target(analyze-fix COMMAND ${RUN_CLANG_TIDY_EXE} -p ${CMAKE_BINARY_DIR} -fix ${CMAKE_CURRENT_SOURCE_DIR}/${DIRECTORY} -quiet COMMENT "Sanitizing source files" VERBATIM)
   add_custom_target(analyze-check COMMAND ${RUN_CLANG_TIDY_EXE} -p ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${DIRECTORY} &> ${CMAKE_CURRENT_BINARY_DIR}/clang_tidy_report.txt ${CMAKE_CURRENT_BINARY_DIR}/. COMMENT "Verify source files are clang‑tidy compliant" VERBATIM)
endfunction()

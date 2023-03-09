# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Mock_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Mock_autogen.dir/ParseCache.txt"
  "Mock_autogen"
  )
endif()

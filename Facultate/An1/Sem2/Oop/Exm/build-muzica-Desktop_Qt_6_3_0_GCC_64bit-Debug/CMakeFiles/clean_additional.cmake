# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/muzica_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/muzica_autogen.dir/ParseCache.txt"
  "muzica_autogen"
  )
endif()

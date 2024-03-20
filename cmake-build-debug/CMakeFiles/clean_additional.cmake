# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Avia_autogen"
  "CMakeFiles/Avia_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Avia_autogen.dir/ParseCache.txt"
  )
endif()

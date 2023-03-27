# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\UniversalGamingApp_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\UniversalGamingApp_autogen.dir\\ParseCache.txt"
  "UniversalGamingApp_autogen"
  )
endif()

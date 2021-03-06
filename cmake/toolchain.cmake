# default max_path length is 260.  Ninja fails if >245 chars.  This option lets cmake use tricks to shrink the path.
if( NOT CMAKE_HOST_UNIX)
  set(CMAKE_OBJECT_PATH_MAX 240)
endif()

set(TOOLCHAIN "armcc" CACHE STRING "Toolchain used for compiling the target")
set_property(CACHE TOOLCHAIN PROPERTY STRINGS "armgcc" "armcc")

if (EXISTS "${CMAKE_CONFIG_DIR}/toolchain/${TOOLCHAIN}.cmake")
    include("${CMAKE_CONFIG_DIR}/toolchain/${TOOLCHAIN}.cmake")
else ()
    message(FATAL_ERROR "Toolchain \"${TOOLCHAIN}\" not recognized.")
endif ()
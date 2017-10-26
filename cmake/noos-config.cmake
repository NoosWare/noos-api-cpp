# - Config file for the NOOS package
# It defines the following variables
#  NOOS_INCLUDE_DIRS - include directories for NOOS
#  NOOS_LIBRARIES    - libraries to link against
#  NOOS_STATIC_LIBRARIES - static libraries to link against

if(EXISTS ${CMAKE_INSTALL_PREFIX}/lib/libnoos.a) 
  set(NOOS_STATIC_LIBRARIES
      ${CMAKE_INSTALL_PREFIX}/lib/libnoos.a
      CACHE INTERNAL "" FORCE
  )
endif()

if(EXISTS ${CMAKE_INSTALL_PREFIX}/lib/libnoos.so)
  set(NOOS_LIBRARIES
      ${CMAKE_INSTALL_PREFIX}/lib/libnoos.so
      CACHE INTERNAL "" FORCE
  )
endif()

set(NOOS_INCLUDE_DIRS
    ${CMAKE_INSTALL_PREFIX}/include/noos
    CACHE INTERNAL "" FORCE
)

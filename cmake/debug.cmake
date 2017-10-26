cmake_minimum_required(VERSION 2.8)
##
# @version 0.8.0
# @date 29.09.2017
#
# Get from arguments if Debug is requested
#
###
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_BUILD_TYPE Debug)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")
    message(STATUS "${BoldGreen}Building: ${CMAKE_BUILD_TYPE}. Ommit flag to change to `Release`${ColourReset}")
else()
    set(CMAKE_BUILD_TYPE Release)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s -O3")
    message(STATUS "Building: ${CMAKE_BUILD_TYPE}. Add flag ${Cyan}`-DCMAKE_BUILD_TYPE=Debug` ${ColourReset} to switch to `Debug`")
endif()

####
set(CMAKE_COLOR_MAKEFILE on)
set(CMAKE_VERBOSE_MAKEFILE off)

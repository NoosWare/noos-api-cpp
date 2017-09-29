cmake_minimum_required(VERSION 2.8)
##
# @version 0.8.0
# @date 29.09.2017
#
# Linux should be the default OS/Platform for NOOS::API 
# We need g++ 4.9 or higher, else json won't work
# We could support 4.8.4 using c++1y only if we change json library.
#
###
message (STATUS "Platform is `${CMAKE_SYSTEM_NAME}`" )

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # get compiler version
    execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    # Check GCC supports C++14
    if (GCC_VERSION VERSION_GREATER 4.9 OR GCC_VERSION VERSION_EQUAL 4.9)
        message(STATUS "Compiler: g++ version >= 4.9 using C++14")  
    elseif ()
        message (FATAL_ERROR "g++ version >= 4.9 is required")
    endif()
# OSX platform
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # get clang version
    execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    if (CLANG_VERSION_MAJOR VERSION_GREATER 3 OR CLANG_VERSION_MAJOR VERSION_EQUAL 3)
        message(STATUS "Info: Clang >= 3.0 using C++14")
    elseif ()
        message(FATAL_ERROR "Clang version >= 3.0 is required")
    endif()
# Intel Compiler May run on Linux - Maybe we should support it
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    message (FATAL_ERROR "unsupported compiler")
# We cannot support Microsoft Visual Studio - We cannot support Win32 platforms
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message (FATAL_ERROR "unsupported compiler")
endif()

###
# Various info
#
message(STATUS "CXX Flags: " ${CMAKE_CXX_FLAGS})
message(STATUS "CXX Link Flags: " ${CMAKE_EXE_LINKER_FLAGS})
message(STATUS "C compiler: " ${CMAKE_C_COMPILER})
message(STATUS "CXX compiler: " ${CMAKE_CXX_COMPILER})

cmake_minimum_required(VERSION 2.8)
##
# @version 0.8.0
# @date 29.09.2017
#
# Finding packages and libraries
#
###
find_package(Threads REQUIRED)

###
# Find libcrypt / libssl - we use it for TLS/SSL sockets
#
find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
    message(STATUS "${Green}Using OpenSSL Version: ${OPENSSL_VERSION} ${ColourReset}")
	message(STATUS "OpenSSL Headers: ${OPENSSL_INCLUDE_DIR}")
endif()
###
# Find Boost - we use it for a variety of operations
#
find_package(Boost COMPONENTS system REQUIRED)
if (Boost_FOUND)
	set(Boost_USE_STATIC_LIBS OFF)
	set(BUILD_SHARED_LIBS ON)
	include_directories(${Boost_INCLUDE_DIR})
    message(STATUS "${Green}Using Boost Version: ${Boost_VERSION} ${ColourReset}")
    message(STATUS "Boost Headers: ${Boost_INCLUDE_DIRS}")
endif()

# Check if we have JSON.hpp from 
# else download it into noos/misc/json.hpp
#
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/noos/misc/json.hpp")
    message(STATUS "${BoldWhite}header `json.hpp` already exists, not downloading${ColourReset}")
else()
    set(wget_command "wget")
    set(wget_arg "https://raw.githubusercontent.com/nlohmann/json/master/src/json.hpp")
    message(STATUS "${BoldGreen}fetching json.hpp header${ColourReset}")
    execute_process(COMMAND ${wget_command} ${wget_arg}
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/noos/misc/)
endif()

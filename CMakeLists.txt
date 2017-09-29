# date June 2017
# @author Alex Giokas <a.gkiokas@ortelio.co.uk>
# CMake flags in use:
#       -DBUILD_SHARED=ON		                        (Default: compile a shared libnoos)
#       -DBUILD_STATIC=ON		                        (Optional: compile a static libnoos)
#       -DBUILD_TESTS=ON                                (Optional: compile various tests - run with `make test`)
#       -DBUILD_EXAMPLES=ON                             (Optional: compile various examples)
#       -DCMAKE_BUILD_TYPE=Debug                        (Optional: enable debug symbols)
#       -DSTATIC_LIBSTD=ON                              (Optional: compile statically against libstdc++)
#       -DOPEN_NAO=ON                                   (Optional: compiling for NAO requires additional CXX flags)
#		-DCMAKE_INSTALL_PREFIX=/usr	                    (Optional: specify the library install directory
#       -DOPENSSL_ROOT_DIR=/usr/local/opt/openssl       (Optional: specify OpenSSL root directory)
#       -DOPENSSL_LIBRARIES=/usr/local/opt/openssl/lib/ (Optional: specify OpenSSL library directory)
#
# After succesfull compilation, run as su/sudo: `make install`
# 
PROJECT(noos)
set (NOOS_VERSION_MAJOR 0)
set (NOOS_VERSION_MINOR 7)
set (NOOS_VERSION_PATCH 3)
set (NOOS_VERSION_STRING ${NOOS_VERSION_MAJOR}.${NOOS_VERSION_MINOR}.${NOOS_VERSION_PATCH})
cmake_minimum_required(VERSION 2.8)

# library paths
set(LIBRARY_PATH ${LIBRARY_PATH}
		      /lib
		      /usr/lib
		      /usr/lib64
		      /usr/local/lib
		      /usr/local/lib64
		      /usr/lib/x86_64-linux-gnu)

# header paths
set(INCLUDE_HEADERS ${INCLUDE_HEADERS} /usr/include/)
include_directories(SYSTEM ${INCLUDE_HEADERS})
set(INCLUDES ${INCLUDES} noos)
include(${INCLUDES}/CMakeLists.txt)

# set root at `/includes`
add_subdirectory(${INCLUDES})
set(CMAKE_MACOSX_RPATH 1)

message("Build directory: ${CMAKE_CURRENT_BINARY_DIR}")

# include everything from "/includes"
include_directories(".")

###
# Set library sources
#
add_library(lnoos OBJECT ${SOURCES})

###
# Include all our custom cmake scripts
###
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/colours.cmake")
file(GLOB cmake_includes "${CMAKE_CURRENT_SOURCE_DIR}/cmake/*.cmake")
foreach(cmake_inc ${cmake_includes})
    include(${cmake_inc})
endforeach()

###
#   Static Library - only if asked 
#	Use only if you want complete static linking
###
if (${BUILD_STATIC})
    #
    # set target, add library - link with Boost and OpenSSL
	#
    set(LIBTARGET ${LIBTARGET} noos)
    add_library(${LIBTARGET} STATIC $<TARGET_OBJECTS:lnoos>)
    set_target_properties(${LIBTARGET} PROPERTIES VERSION ${NOOS_VERSION_STRING})
    set_target_properties(${LIBTARGET} PROPERTIES SUFFIX ".a.${NOOS_VERSION_STRING}")
    target_link_libraries(${LIBTARGET} ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES} ${CMAKE_DL_LIBS})
	#
	# set linking to fully static (libc, libstdc++, etc)
	#
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}-static")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-std=c++1y -Wall -fPIC")
#
#####################################################################################
#  Open NAO: requires special instructions for Intel ATOM
#  Current NAO is Gentoo 2.6.33.9-rt31-aldebaran-rt
#
elseif(${OPEN_NAO})
    #
    # set target, add library - link with Boost and OpenSSL
    #
    set(LIBTARGET ${LIBTARGET} noos)
	add_library(${LIBTARGET} STATIC $<TARGET_OBJECTS:lnoos>)
    set_target_properties(${LIBTARGET} PROPERTIES VERSION ${NOOS_VERSION_STRING})
    set_target_properties(${LIBTARGET} PROPERTIES SUFFIX ".a.${NOOS_VERSION_STRING}")
    target_link_libraries(${LIBTARGET} ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
    ###
	# No need to build static library, but the apps will have to statically link
    #
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_CXX_FLAGS 
	"${CMAKE_CXX_FLAGS}-std=gnu++1y -Wall -fPIC -Os -s -O2 -march=atom -mtune=atom -mfpmath=sse -fschedule-insns -fsched-pressure")
    # 
###
#   Shared Library - By default
###
else()
    #
    # use shared boost - build shared libs - set correct flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-std=c++1y -Wall -fPIC -D_GLIBCXX_DEBUG")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
	#
    # build library first
    set(LIBTARGET ${LIBTARGET} noos)
    add_library(${LIBTARGET} SHARED $<TARGET_OBJECTS:lnoos>)
    set_target_properties(${LIBTARGET} PROPERTIES VERSION ${NOOS_VERSION_STRING} SOVERSION ${NOOS_VERSION_STRING})
    target_link_libraries(${LIBTARGET} ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
    set_target_properties(${LIBTARGET} PROPERTIES INSTALL_PATH "${CMAKE_INSTALL_PREFIX}/lib")
    message(STATUS "${BoldBlue}Building Shared library: lib${LIBTARGET} ${ColourReset}")
	#
endif()

###
#   build tests - run with `make test`
###
if(${BUILD_TESTS})
    if ((${NOOS_STATIC}) OR (${OPEN_NAO}))
        message(WARNING "Not going to build tests using Static/Open NAO library, use shared library for testing")
    else()
        enable_testing()
        build_tests()
    endif()
else()
    message(STATUS "Not Building Unit tests. Enable with ${Cyan}`-DBUILD_TESTS=ON`${ColourReset}")
endif()

####
##   build examples
####
if (${BUILD_EXAMPLES})
    build_examples() 
else()
    message(STATUS "Not Building examples. Enable them with ${Cyan}`-DBUILD_EXAMPLES=ON`${ColourReset}")
endif()

###
# Install library 
#
install_library()
#
# Install rapp-config.cmake
#
install_config()

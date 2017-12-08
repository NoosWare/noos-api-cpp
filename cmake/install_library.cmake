cmake_minimum_required(VERSION 2.8)
##
# @version 0.8.0
# @date 29.09.2017
#
# Installing library
#
###
function(install_library)
    set(LIB_VERSION ${NOOS_VERSION_MAJOR}.${NOOS_VERSION_MINOR}.${NOOS_VERSION_PATCH})
    #
    # symbolic link library version to the generic name
    #
    if((${NOOS_STATIC}) OR (${OPEN_NAO}))
        install(TARGETS ${LIBTARGET} DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/")
        install(CODE 
            "EXECUTE_PROCESS(COMMAND ln -sf ${CMAKE_INSTALL_PREFIX}/lib/libnoos.a.${LIB_VERSION}
                                            ${CMAKE_INSTALL_PREFIX}/lib/libnoos.a)")
    else()
        install(TARGETS ${LIBTARGET} DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/")
        install(CODE 
            "EXECUTE_PROCESS(COMMAND ln -sf ${CMAKE_INSTALL_PREFIX}/lib/libnoos.so.${LIB_VERSION} 
                                            ${CMAKE_INSTALL_PREFIX}/lib/libnoos.so)")
    endif()
    message(STATUS "Installing library in: `${CMAKE_INSTALL_PREFIX}/lib`")
    #
    # Headers go under /usr/loca/include
    #
    install(DIRECTORY ${INCLUDES}/ DESTINATION "${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}" 
                      FILES_MATCHING PATTERN "*.hpp" PATTERN "*.ihh" PATTERN "*.tpl" PATTERN "noos")
    message(STATUS "Installing Headers in: `${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}`")
endfunction(install_library)

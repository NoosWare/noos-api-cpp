cmake_minimum_required(VERSION 2.8)
##
# @version 0.8.0
# @date 29.09.2017
#
# Install config.cmake
#
###
function(install_config)
    configure_file(cmake/noos-config.cmake
                   "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/noos-config.cmake"
                   COPYONLY
                  )
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/noos-config.cmake
            DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/noos/")
    message(STATUS "Installing noos-config.cmake in ${CMAKE_INSTALL_PREFIX}/lib/cmake/noos/")
endfunction(install_config)

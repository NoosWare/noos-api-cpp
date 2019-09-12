cmake_minimum_required(VERSION 2.8)
##
# @version 0.8.0
# @date 29.09.2017
#
# Build examples
#
###
function(build_examples)
    if ((${OPEN_NAO}) OR (${BUILD_STATIC}))
        message(STATUS "${BoldYellow}Not going to build examples using Static/Open NAO library, use shared library ${ColourReset}")
    else()
        set (EXAMPLES available_services.cpp
                      age_detection.cpp
                      face_detection.cpp
                      face_detection_opencv.cpp
                      face_expression.cpp
                      gender_detection.cpp
                      human_detection.cpp
                      object_recognition.cpp
                      qr_recognition.cpp
                      orb.cpp
                      upload_delete_maps.cpp
                      face_recognition.cpp
                      class.cpp
                      custom_error_handler.cpp
                      chatbot.cpp
                      object_detection.cpp
                     )
        set(EXAMPLE_DIR ${EXAMPLE_DIR} examples)
        message(STATUS "${BoldGreen}Building examples, they will be placed under `${CMAKE_CURRENT_BINARY_DIR}/${EXAMPLE_DIR}` ${ColourReset}")
        # create "/examples"
        add_custom_command(TARGET ${LIBTARGET} POST_BUILD
                           COMMAND ${CMAKE_COMMAND} -E make_directory ${EXAMPLE_DIR})
        # symlink `/tests/data` instead of copying
        add_custom_command(TARGET ${LIBTARGET} POST_BUILD
                           COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/tests/data ${EXAMPLE_DIR}/data)
        # symlink `shared library`
        add_custom_command(TARGET ${LIBTARGET} POST_BUILD
                           COMMAND ${CMAKE_COMMAND} -E create_symlink 
                           ${CMAKE_CURRENT_BINARY_DIR}/lib${LIBTARGET}.so 
                           ${EXAMPLE_DIR}/lib${LIBTARGET}.so.${NOOS_VERSION_STRING})
        # iterate tests
        foreach(ITEM ${EXAMPLES})
            string(REPLACE ".cpp" "" TARGET ${ITEM})
            add_executable(${TARGET} ${EXAMPLE_DIR}/${ITEM})
            target_link_libraries(${TARGET} ${LIBTARGET} ${Noos_DEPENDENCIES} ${CMAKE_THREAD_LIBS_INIT})
            message(STATUS "${Yellow} ${TARGET} ${ColourReset}")
            add_custom_command(TARGET ${TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${TARGET} ${EXAMPLE_DIR}/.)
            add_custom_command(TARGET ${TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E remove ${TARGET})
        endforeach(ITEM)
    endif()
endfunction(build_examples)

cmake_minimum_required(VERSION 2.8)
##
# @version 0.8.0
# @date 29.09.2017
#
# Build tests
#
###
function(build_tests)
		if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/catch.hpp")
			message(STATUS "${BoldWhite}header `catch.hpp` already exists, not downloading.${ColourReset}")
		else()
			set(wget_command "wget")
            set(wget_arg "https://raw.githubusercontent.com/catchorg/Catch2/master/single_include/catch2/catch.hpp")
			message(STATUS "${BoldGreen}fetching catch.hpp single header.${ColourReset}")
			execute_process(COMMAND ${wget_command} ${wget_arg}
							WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests/)
		endif()
        set(TESTS ${TESTS} tests)
        set(TESTFILES ${TESTFILES} asio_classes.cpp 
                                   json_classes.cpp 
                                   object_classes.cpp
                                   cloud_calls.cpp)
        set(TEST_DIR ${TEST_DIR} tests)
        message(STATUS "${BoldGreen}Building tests, they will be placed under directory `${CMAKE_CURRENT_BINARY_DIR}/${TEST_DIR}` ${ColourReset}")
        # create "/tests"
        add_custom_command(TARGET ${LIBTARGET} POST_BUILD
                           COMMAND ${CMAKE_COMMAND} -E make_directory ${TEST_DIR})
        # symlink `/tests/data` instead of copying
        add_custom_command(TARGET ${LIBTARGET} POST_BUILD
                           COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/${TESTS}/data ${TEST_DIR}/data)
        # symlink `shared library`
        add_custom_command(TARGET ${LIBTARGET} POST_BUILD
                           COMMAND ${CMAKE_COMMAND} -E create_symlink 
                           ${CMAKE_CURRENT_BINARY_DIR}/lib${LIBTARGET}.so 
                           ${TEST_DIR}/lib${LIBTARGET}.so.${NOOS_VERSION_STRING})
        # iterate tests
        foreach(ITEM ${TESTFILES})
            string(REPLACE ".cpp" "" TARGET ${ITEM})
            add_executable(${TARGET} ${TESTS}/${ITEM})
            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
            target_link_libraries(${TARGET} ${LIBTARGET} ${CMAKE_THREAD_LIBS_INIT})
            message(STATUS "${Magenta} ${TARGET} ${ColourReset}")
            add_custom_command(TARGET ${TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${TARGET} ${TEST_DIR}/.)
            add_custom_command(TARGET ${TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E remove ${TARGET})
            add_test(${TARGET} ${TEST_DIR}/${TARGET})
        endforeach(ITEM)
endfunction(build_tests)

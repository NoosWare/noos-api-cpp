cmake_minimum_required(VERSION 2.8)
set(SOURCE_DIR ${SOURCE_DIR} noos)
# cloud
file(GLOB cpp_files "${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_DIR}/cloud/*.cpp")
foreach(cpp_file ${cpp_files})
   list(APPEND SOURCES ${cpp_file})
endforeach()
# asio
file(GLOB cpp_files "${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_DIR}/cloud/asio/*.cpp")
foreach(cpp_file ${cpp_files})
   list(APPEND SOURCES ${cpp_file})
endforeach()
# objects
file(GLOB cpp_files "${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_DIR}/objects/*.cpp")
foreach(cpp_file ${cpp_files})
   list(APPEND SOURCES ${cpp_file})
endforeach()
# misc
file(GLOB cpp_files "${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_DIR}/misc/*.cpp")
foreach(cpp_file ${cpp_files})
   list(APPEND SOURCES ${cpp_file})
endforeach()

######################################################################
# @author      : karl (karlsasssie@gmail.com)
# @file        : CMakeLists
# @created     : Friday Apr 07, 2023 15:39:05 CEST
######################################################################

cmake_minimum_required(VERSION 2.8)
project(can-socketcan-platform C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_library(${PROJECT_NAME} 
  ${CMAKE_CURRENT_SOURCE_DIR}/src/socketcan_socket.c
)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


add_executable(${PROJECT_NAME}-test src/main.c)

target_link_libraries(${PROJECT_NAME}-test PRIVATE ${PROJECT_NAME})


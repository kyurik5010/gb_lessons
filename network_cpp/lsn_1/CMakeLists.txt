cmake_minimum_required(VERSION 3.10)

project(udp-server C CXX)

set(CMAKE_CXX_STANDARD 17 REQUIRED)

set(${PROJECT_NAME}_SRC main.cpp)

source_group(source FILES ${${PROJECT_NAME}_SRC}})

add_executable("${PROJECT_NAME}" "${${PROJECT_NAME}_SRC}")

if(WIN32)
  target_link_libraries("${PROJECT_NAME}" wsock32 ws2_32)
endif()


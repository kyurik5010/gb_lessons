cmake_minimum_required(VERSION 3.10)

project(cpp-network-lessons)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(ENV{OPENSSL_ROOT_DIR} /usr/local/Cellar/openssl@3/3.0.5)

if (MSVC)
    set(CMAKE_CXX_STANDARD 20)
else()
    set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (WIN32)
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib;.a;${CMAKE_FIND_LIBRARY_SUFFIXES}")
else()
# BUGGY!
#    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a;${CMAKE_FIND_LIBRARY_SUFFIXES}")
endif()

set(Boost_USE_STATIC_LIBS ON)
set(LINK_SEARCH_START_STATIC ON)
#set(LINK_SEARCH_END_STATIC ON)
set(BUILD_SHARED_LIBS OFF)
# set(CMAKE_EXE_LINKER_FLAGS "-static")

#file(GLOB lessons LIST_DIRECTORIES true "l[1-9]")
#add_subdirectory("socket_wrapper")
add_subdirectory("l1")
#add_subdirectory("l2")
#add_subdirectory("l3")
#add_subdirectory("l4")
#add_subdirectory("l5") # тут проблема с Qt
#add_subdirectory("l6") # тут проблема с jwt
#add_subdirectory("l7") # тут проблема с restbed
#add_subdirectory("l8") # тут проблема с Qt
#foreach(lesson ${lessons})
#  add_subdirectory("${lesson}")
#endforeach()


message("\nTakoe build done\n")
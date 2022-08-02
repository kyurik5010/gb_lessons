cmake_minimum_required(VERSION 3.21)
project(tough_cpp_lsn7)

set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64" CACHE STRING "")
set(CMAKE_CXX_COMPILER_ID "Clang")
set(CMAKE_CXX_COMPILER /Library/Developer/CommandLineTools/usr/bin/c++)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -std=c++11)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_LINKER /Library/Developer/CommandLineTools/usr/bin/ld)
set(CMAKE_CXX_COMPILER_ABI )


#find_package(Protobuf REQUIRED)

#if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#    conan_basic_setup()
#else()
#    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
#endif()


add_executable(tough_cpp_lsn7 main.cpp)
#target_link_libraries(tough_cpp_lsn7 PUBLIC /Users/urijmihajlovic/GPB/protobuf-3.21.1/src/)
target_include_directories(tough_cpp_lsn7 PUBLIC /Users/urijmihajlovic/GPB/protobuf-3.21.1/src/)


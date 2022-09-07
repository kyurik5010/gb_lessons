cmake_minimum_required(VERSION 3.2)

project("boost_server")

find_package(Boost REQUIRED)

set(CMAKE_CXX_STANDARD 17 REQUIRED)

set(BOOST_INC "/usr/local/cellar/boost/1.79.0_1/include/")
#set(BOOST_LIB_DIR "/usr/local/cellar/boost/1.79.0_1/lib")
#set(BOOST_LIBS
#        ${BOOST_LIB_DIR}/
#        )

include_directories(${BOOST_INC})

add_executable(serv main.cpp)

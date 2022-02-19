cmake_minimum_required(VERSION 3.21)
project(dachi_case)

set(CMAKE_CXX_STANDARD 14)

add_executable(dachi_case main.cpp Game.cpp Game.h Quests.cpp Quests.h)

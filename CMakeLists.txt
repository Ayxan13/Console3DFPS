cmake_minimum_required(VERSION 3.17)
project(ConsoleFPS)

set(CMAKE_CXX_STANDARD 20)

add_executable(ConsoleFPS main.cpp Map.hpp Screen.hpp Player.hpp StopWatch.hpp)
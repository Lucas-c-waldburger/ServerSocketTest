cmake_minimum_required(VERSION 3.24)
project(socket)

set(CMAKE_CXX_STANDARD 17)

add_executable(socket main.cpp Utils.cpp Utils.h includes.h LoopAccept.cpp LoopAccept.h)

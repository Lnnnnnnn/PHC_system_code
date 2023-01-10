cmake_minimum_required(VERSION 3.21)
project(SSFunc_v4_hw)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SSFunc_v4_hw
        ap_header.h
        Cost_function.cpp
        main.cpp
        math.cpp
        Statespace_function.cpp)


include_directories("D:/Xilinx/Vitis_HLS/2021.2/include")


cmake_minimum_required(VERSION 3.21)
project(TRANS_v2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(TRANS_v2
        ap_header.h
        main.cpp
        math.cpp
        TransFunc.cpp)
include_directories("D:/Xilinx/Vitis_HLS/2021.2/include")


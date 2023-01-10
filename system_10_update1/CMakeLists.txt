cmake_minimum_required(VERSION 3.21)
project(PHC_v51_traceback_update7)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(PHC_v51_traceback_update7
        ap_header.h
        main.cpp
        math.cpp
        MPCcore.cpp
        ThreadFunction.cpp)

include_directories("D:/Xilinx/Vitis_HLS/2021.2/include")

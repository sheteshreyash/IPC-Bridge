cmake_minimum_required(VERSION 3.10)
project(telemetry_reader CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(telemetry_reader main.cpp)
target_include_directories(telemetry_reader PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../../shared)

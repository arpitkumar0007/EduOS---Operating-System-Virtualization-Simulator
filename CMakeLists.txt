cmake_minimum_required(VERSION 3.10)
project(EduOS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(EduOS
    main.cpp
    Simulation.cpp
    MMU.cpp
)

target_include_directories(EduOS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
cmake_minimum_required(VERSION 3.16)
project(NBodySim)

set(CMAKE_CXX_STANDARD 17)

add_executable(nbody-sim
    src/main.cpp
    src/body.cpp
    src/simulation.cpp
)

target_include_directories(nbody-sim PRIVATE include)

target_link_libraries(nbody-sim sfml-graphics sfml-window sfml-system)
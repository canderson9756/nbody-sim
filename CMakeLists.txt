cmake_minimum_required(VERSION 3.16)
project(NBodySim)

set(CMAKE_CXX_STANDARD 17)

add_executable(nbody-sim
    src/main.cpp
    src/body.cpp
    src/simulation.cpp
    src/integrator2d.cpp
)

target_include_directories(nbody-sim PRIVATE
    ${SFML_INCLUDE_DIRS}
    ${X11_INCLUDE_DIR}
    include
)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(X11 REQUIRED)
target_link_libraries(nbody-sim PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    ${X11_LIBRARIES}
)
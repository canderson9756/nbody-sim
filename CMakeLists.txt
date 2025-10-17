cmake_minimum_required(VERSION 3.16)
project(NBodySim)

set(CMAKE_CXX_STANDARD 17)

add_executable(nbody-sim
    src/main.cpp
    src/body.cpp
    src/simulation.cpp
    src/integrator2d.cpp
    src/parser.cpp
)

target_include_directories(nbody-sim PRIVATE
    ${SFML_INCLUDE_DIRS}
    ${X11_INCLUDE_DIR}
    src/simulation.h
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
include(FetchContent)

FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG yaml-cpp-0.7.0 # Can be a tag (yaml-cpp-x.x.x), a commit hash, or a branch name (master)
)
FetchContent_MakeAvailable(yaml-cpp)

target_link_libraries(nbody-sim PUBLIC yaml-cpp::yaml-cpp) # The library or executable that require yaml-cpp library
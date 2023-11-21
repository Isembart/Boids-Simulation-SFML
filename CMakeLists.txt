cmake_minimum_required(VERSION 3.16)
project(QuadTreeTest LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)


# SET(CMAKE_CXX_FLAGS  "-pg -no-pie -O2")
# SET(CMAKE_CXX_FLAGS  "-O3")

execute_process(COMMAND git submodule update --init --recursive)

add_subdirectory(libs/SFML)

set(SOURCE src/main.cpp src/quadTree.cpp src/gameObject.cpp src/particle.cpp src/vectorFunctions.cpp)

add_executable(QuadTreeTest ${SOURCE})
target_link_libraries(QuadTreeTest PRIVATE sfml-graphics)
target_compile_features(QuadTreeTest PRIVATE cxx_std_17)

#my
target_include_directories(QuadTreeTest PUBLIC include)

install(TARGETS QuadTreeTest)

cmake_minimum_required(VERSION 3.16)
project(BoidsSimulation LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# SET(CMAKE_CXX_FLAGS  "-pg -no-pie -O2")
# SET(CMAKE_CXX_FLAGS  "-O3")

execute_process(COMMAND git submodule update --init --recursive)

add_subdirectory(libs/SFML)
add_subdirectory(libs/googletest)

set(SOURCE src/main.cpp src/quadTree.cpp src/gameObject.cpp src/particle.cpp src/vectorFunctions.cpp)

add_executable(BoidsSimulation ${SOURCE})
target_link_libraries(BoidsSimulation PRIVATE sfml-graphics)
target_compile_features(BoidsSimulation PRIVATE cxx_std_17)

#my
target_include_directories(BoidsSimulation PUBLIC include)

# add tests
enable_testing()
add_subdirectory(tests)
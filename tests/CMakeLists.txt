# Write a cmakelists to build tests
cmake_minimum_required(VERSION 3.16)
project(Tests)

#because I don't want to create a library from my source files, I just add them to the test executable
#This may change

set(SOURCES
    ../src/gameObject.cpp
    ../src/particle.cpp
    ../src/quadTree.cpp
    ../src/vectorFunctions.cpp
    gameObjectTest.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

#include the headers
target_include_directories(${PROJECT_NAME} PUBLIC
    ../include
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    sfml-graphics
    gtest_main
)

add_test(NAME BoidsTests 
    COMMAND ${PROJECT_NAME}
)



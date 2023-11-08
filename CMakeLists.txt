cmake_minimum_required(VERSION 3.16)
project(QuadTreeTest LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# SET(CMAKE_CXX_FLAGS  "-pg -no-pie -O2")
SET(CMAKE_CXX_FLAGS  "-O3")

set(SOURCE src/main.cpp src/quadTree.cpp src/gameObject.cpp src/particle.cpp src/vectorFunctions.cpp)

add_executable(QuadTreeTest ${SOURCE})
target_link_libraries(QuadTreeTest PRIVATE sfml-graphics)
target_compile_features(QuadTreeTest PRIVATE cxx_std_17)

#my
target_include_directories(QuadTreeTest PUBLIC include)

if(WIN32)
    add_custom_command(
        TARGET QuadTreeTest
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:QuadTreeTest>
        VERBATIM)
endif()

install(TARGETS QuadTreeTest)

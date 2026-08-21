cmake_minimum_required(VERSION 3.16)

project(toolbox_cpp LANGUAGES CXX)

add_library(toolbox INTERFACE)
target_include_directories(toolbox INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_features(toolbox INTERFACE cxx_std_17)

add_library(toolbox::toolbox ALIAS toolbox)

add_executable(toolbox_example examples/main.cpp)
target_link_libraries(toolbox_example PRIVATE toolbox::toolbox)

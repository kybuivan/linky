cmake_minimum_required(VERSION 3.26.0 FATAL_ERROR)

set(target_name parser)
project(${target_name} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

file(GLOB_RECURSE libsrc src/*.cpp src/*.c src/*.cc)

add_library(${target_name} STATIC ${libsrc})

include(cereal)
target_link_libraries(${target_name} PUBLIC
    external::cereal
)

target_include_directories(${target_name} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_precompile_headers(${target_name}
    INTERFACE
    <string>
)

# enable testing functionality
enable_testing()

# testing binary
add_executable(${target_name}_test test/test.cpp)
target_link_libraries(${target_name}_test PRIVATE ${target_name})

# define tests
add_test(
  NAME ${target_name}_test
  COMMAND $<TARGET_FILE:${target_name}_test>
)
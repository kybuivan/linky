cmake_minimum_required(VERSION 3.24.0 FATAL_ERROR)

project(linky CXX C)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_VS_PLATFORM_NAME "x64")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/external)

# Global configuration types
set(CMAKE_CONFIGURATION_TYPES
    "Debug"
    "Release"
    "Distribution"
    CACHE STRING "" FORCE
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Sub-projects
add_subdirectory(src)
add_subdirectory(editor)
add_subdirectory(test)

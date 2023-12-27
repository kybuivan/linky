# 
# Copyright (c) 2023-2024 Ky Bui Van
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

if(TARGET external::stb)
    return()
endif()

message(STATUS "Third-party (external): creating target 'external::stb'")

include(FetchContent)

FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
)
FetchContent_MakeAvailable(stb)

# Generate implementation file
file(WRITE "${stb_BINARY_DIR}/stb_image.cpp.in" [[
    #define STB_IMAGE_IMPLEMENTATION
    #include <stb_image.h>

    #define STB_IMAGE_WRITE_IMPLEMENTATION
    #include <stb_image_write.h>
]])

configure_file(${stb_BINARY_DIR}/stb_image.cpp.in ${stb_BINARY_DIR}/stb_image.cpp COPYONLY)

# Define stb library
add_library(stb ${stb_BINARY_DIR}/stb_image.cpp ${stb_SOURCE_DIR}/stb_vorbis.c)
target_include_directories(stb PUBLIC "${stb_SOURCE_DIR}")

add_library(external::stb ALIAS stb)
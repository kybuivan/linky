#
# Copyright (c) 2023 Ky Bui Van
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

if(TARGET external::catch)
    return()
endif()

message(STATUS "Third-party (external): creating target 'external::catch'")

include(FetchContent)

FetchContent_Declare(catch
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0
)

option(CATCH_INSTALL_DOCS "Install documentation alongside library" OFF)
FetchContent_MakeAvailable(catch)

add_library(external::catch ALIAS Catch2WithMain)

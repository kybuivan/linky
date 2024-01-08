cmake_minimum_required(VERSION 3.26.0 FATAL_ERROR)

file(STRINGS "version.txt" LINKY_VERSION)

project(Linky
    VERSION ${LINKY_VERSION}
    DESCRIPTION "A high performance focused game engine using object oriented techniques based in the latest C++"
    LANGUAGES CXX
)

set(CMAKE_POLICY_DEFAULT_CMP0076 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
cmake_policy(SET CMP0076 NEW)
cmake_policy(SET CMP0077 NEW)
cmake_policy(SET CMP0127 NEW)

# Standard CMake Includes
include(CTest)
include(FetchContent)
include(GNUInstallDirs)
include(CMakeDependentOption)
include(CMakePackageConfigHelpers)

option(LINKY_USE_ALT_NAMES "Use alternative names for the project, such as naming the include directory all lowercase." ON)
option(LINKY_GENERATE_EXPORT_HEADER "Create a `project_export.h` file containing all exported symbols." OFF)
cmake_dependent_option(LINKY_CODE_COVERAGE "Enable code coverage" ON "\"${CMAKE_CXX_COMPILER_ID}\" STREQUAL \"Clang\" OR \"${CMAKE_CXX_COMPILER_ID}\" STREQUAL \"GNU\"" OFF)
cmake_dependent_option(LINKY_INCLUDE_NATVIS "Enable inclusion of a natvis files for debugging" ON "\"${CMAKE_CXX_COMPILER_ID}\" STREQUAL \"MSVC\"" OFF)

set(BUILD_SHARED_LIBS OFF)

list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/external
)

include(compiler)
enable_testing()

# Offer the user the choice of overriding the installation directories
set(INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR} CACHE PATH "Installation directory for libraries")
set(INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR} CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR} CACHE PATH "Installation directory for header files")

# Build the RPath relative to the executable locations (i.e. from the bin directory, up back to the install root and in to the lib folder.
file(RELATIVE_PATH LINKY_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/${INSTALL_BINDIR} ${CMAKE_INSTALL_PREFIX})
if (APPLE)
    set(LINKY_INSTALL_RPATH "@executable_path/${LINKY_INSTALL_RPATH}")
else()
    set(LINKY_INSTALL_RPATH "$ORIGIN/${LINKY_INSTALL_RPATH}")
endif()
file(TO_NATIVE_PATH "${LINKY_INSTALL_RPATH}/${INSTALL_LIBDIR}" LINKY_INSTALL_RPATH )

set(CMAKE_INSTALL_RPATH ${LINKY_INSTALL_RPATH})
set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
set(CMAKE_SKIP_BUILD_RPATH  FALSE)

get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(IS_MULTI_CONFIG)
    set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)
    set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>)
    file(RELATIVE_PATH LINKY_RELATIVE_BUILD_RPATH ${RUNTIME_OUTPUT_DIRECTORY} ${LIBRARY_OUTPUT_DIRECTORY})
    if (APPLE)
        set(LINKY_BUILD_RPATH "@executable_path/${LINKY_RELATIVE_BUILD_RPATH}")
    else()
        set(LINKY_BUILD_RPATH "$ORIGIN/${LINKY_RELATIVE_BUILD_RPATH}")
    endif()

    set(CMAKE_BUILD_RPATH ${LINKY_BUILD_RPATH})
    set(CMAKE_BUILD_WITH_INSTALL_RPATH OFF)
endif()

# Sub-projects
add_subdirectory(engine)
#add_subdirectory(editor)
add_subdirectory(test)
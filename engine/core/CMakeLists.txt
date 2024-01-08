#add_subdirectory(templates)
add_library(linky_core STATIC)
add_library(linky::core ALIAS linky_core)

target_include_directories(linky_core
    PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
)

target_sources(linky_core
    PUBLIC
        core.hpp
        platform.hpp
        typedefs.hpp
    PRIVATE
        core.cpp
)

target_link_libraries(linky_core PUBLIC
    linky::config
)

add_subdirectory(reflection)

target_compile_features(linky_core PUBLIC cxx_std_23)
target_compile_options(linky_core
    PRIVATE
#        -enable-hosted-libstdcxx
	    $<$<CXX_COMPILER_ID:MSVC>:/wd4251> # class 'foo' needs to have dll-interface to be used by clients of class 'bar'
)
get_target_property(SOURCES_FILES linky_core SOURCES)
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCES_FILES})

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
include(GenerateExportHeader)
generate_export_header(linky_core)
configure_file(${CMAKE_CURRENT_BINARY_DIR}/linky_core_export.h ${CMAKE_INSTALL_INCLUDEDIR}/core/linky_core_export.h COPYONLY)

# Get Git commit hash
execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/version.hpp.in
    ${CMAKE_INSTALL_INCLUDEDIR}/core/version.hpp
    @ONLY
)

install(TARGETS linky_core
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/core
)

# Hierarchically copy headers to the install dir
install (
    DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}/core
    FILES_MATCHING PATTERN
        "*.hpp"
)

# install(
#     FILES
#         ${CMAKE_CURRENT_BINARY_DIR}/core/linkycore_export.h
#     DESTINATION
#         ${CMAKE_INSTALL_INCLUDEDIR}/core/
# )
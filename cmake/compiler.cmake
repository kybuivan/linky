include(warnings)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(LinkyConfig INTERFACE)
add_library(linky::config ALIAS LinkyConfig)
target_link_libraries(LinkyConfig
    INTERFACE
        $<$<PLATFORM_ID:Linux>:dl>
)

target_compile_options(LinkyConfig
    INTERFACE
        $<$<CXX_COMPILER_ID:MSVC>:${MSVC_WARNINGS}>
        $<$<CXX_COMPILER_ID:GNU>:${GCC_WARNINGS}>
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:${CLANG_WARNINGS}>
)
include(tracy)
target_link_libraries(linky_core
    PUBLIC
        external::tracy
)

target_sources(linky_core
    PUBLIC
        profiler.hpp
    PRIVATE
        profiler.cpp
)
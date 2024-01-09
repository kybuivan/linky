include(tracy)
include(spdlog)
target_link_libraries(linky_core
    PUBLIC
        external::tracy
        external::spdlog
)

target_sources(linky_core
    PUBLIC
        profiler.hpp
        logger.hpp
    PRIVATE
        profiler.cpp
        logger.cpp
)
include(concurrentqueue)
target_link_libraries(linky_core
    PUBLIC
        external::concurrentqueue
)

target_sources(linky_core
    PUBLIC
        thread_pool.hpp
    PRIVATE
        thread_pool.cpp
)
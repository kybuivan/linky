include(cereal)
target_link_libraries(linky_core
    PUBLIC
        external::cereal
)

target_sources(linky_core
    PUBLIC
        serialization.h
    PRIVATE
        serialization.cpp
)
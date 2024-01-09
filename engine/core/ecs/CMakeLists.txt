include(entt)
target_link_libraries(linky_core
    PUBLIC
        external::entt
)

target_sources(linky_core
    PUBLIC
        entity.hpp
    PRIVATE
        entity.cpp
)
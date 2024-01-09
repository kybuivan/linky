include(glm)
target_link_libraries(linky_core
    PUBLIC
        external::glm
)

target_sources(linky_core
    PUBLIC
        color.hpp
        math.hpp
        math_defs.hpp
        random.hpp
        vector.hpp
    PRIVATE
        math.cpp
)

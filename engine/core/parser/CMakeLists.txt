include(nlohmann_json)
target_link_libraries(linky_core
    PUBLIC
        external::nlohmann_json
)

target_sources(linky_core
    PUBLIC
        parser.hpp
    PRIVATE
        parser.cpp
)
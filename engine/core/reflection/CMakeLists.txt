include(rttr)
include(magic_enum)
target_link_libraries(linky_core
    PUBLIC
        external::rttr
        external::magic_enum
)

target_sources(linky_core
    PUBLIC
        reflection_enum.hpp
        reflection.h
        registration.h
    PRIVATE
        reflection.cpp
)
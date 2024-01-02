file(GLOB_RECURSE src_files "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library(core STATIC ${src_files})

include(glm)
include(spdlog)
include(stb)
include(entt)
include(magic_enum)
include(eventpp)
include(nlohmann_json)
include(cereal)
include(stduuid)
include(lua)
include(sol2)

target_link_libraries(core PUBLIC
  external::glm
  external::spdlog
  external::stb
  external::entt
  external::magic_enum
  external::eventpp
  external::nlohmann_json
  external::cereal
  external::stduuid
  external::lua
  external::sol2
)

# Include directories
target_include_directories(core PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/.."
  "${PROJECT_BINARY_DIR}/include"
)
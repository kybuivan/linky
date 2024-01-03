#add_subdirectory(templates)
add_library(core)
set_warnings_as_errors(core)

# Include directories
target_include_directories(core PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/.."
  "${PROJECT_BINARY_DIR}/include"
)

file(GLOB_RECURSE src_files "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
target_sources(core PRIVATE ${src_files})

include(glm)
include(spdlog)
include(stb)
include(entt)
include(magic_enum)
include(eventpp)
#include(nlohmann_json)
#include(cereal)
include(stduuid)
include(lua)
include(sol2)
include(gsl)
#include(reflectcpp)

target_link_libraries(core PUBLIC
  external::glm
  external::spdlog
  external::stb
  external::entt
  external::magic_enum
  external::eventpp
  #external::nlohmann_json
  #external::cereal
  external::stduuid
  external::lua
  external::sol2
  external::gsl
  #external::reflectcpp
)

target_compile_features(core PUBLIC cxx_std_23)
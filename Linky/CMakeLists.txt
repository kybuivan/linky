set(project_name Linky)

file(GLOB_RECURSE src_files "src/*.hpp" "src/*.cpp")

add_library(${project_name} STATIC ${src_files})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/external)
include(glm)
include(spdlog)
include(stb)
include(assimp)
include(glad)
include(glfw)
include(imgui)
include(imguizmo)
include(imnodes)
include(entt)

target_link_libraries(${project_name} PUBLIC
  external::glm
  external::spdlog
  external::stb
  external::glad
  external::assimp
  external::glfw
  external::imgui
  external::imguizmo
  external::imnodes
  external::entt
)

set (CMAKE_SHARED_LINKER_FLAGS "-Wl,--as-needed")

# Include directories
target_include_directories(${PROJECT_NAME} PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# Compile definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE
  "$<$<CONFIG:Debug>:"
  "LK_DEBUG;"
  "_DEBUG;"
  ">"
  "$<$<CONFIG:Release>:"
  "LK_RELEASE;"
  "NDEBUG;"
  ">"
  "$<$<CONFIG:Distribution>:"
  "LK_DISTRIBUTION;"
  "NDEBUG"
  ">"
  "_CRT_SECURE_NO_WARNINGS"
  "_SILENCE_ALL_CXX20_DEPRECATION_WARNINGS"
  "GLM_FORCE_DEPTH_ZERO_TO_ONE"
)
add_subdirectory(core)
#add_subdirectory(screen)

# set(project_name Linky)

# file(GLOB_RECURSE src_files "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# add_library(${project_name} STATIC ${src_files})

# include(assimp)
# include(glad)
# include(glfw)
# include(imgui)
# include(imguizmo)
# include(imnodes)

# target_link_libraries(${project_name} PUBLIC
#   core
#   external::glad
#   external::assimp
#   external::glfw
#   external::imgui
#   external::imguizmo
#   external::imnodes
# )

# set (CMAKE_SHARED_LINKER_FLAGS "-Wl,--as-needed")

# # Include directories
# target_include_directories(${project_name} PUBLIC
#   "${CMAKE_CURRENT_SOURCE_DIR}"
#   "${PROJECT_BINARY_DIR}/include"
# )

# # Compile definitions
# target_compile_definitions(${project_name} PRIVATE
#   "$<$<CONFIG:Debug>:"
#   "LK_DEBUG;"
#   "_DEBUG;"
#   ">"
#   "$<$<CONFIG:Release>:"
#   "LK_RELEASE;"
#   "NDEBUG;"
#   ">"
#   "$<$<CONFIG:Distribution>:"
#   "LK_DISTRIBUTION;"
#   "NDEBUG"
#   ">"
#   "_CRT_SECURE_NO_WARNINGS"
#   "_SILENCE_ALL_CXX20_DEPRECATION_WARNINGS"
#   "GLM_FORCE_DEPTH_ZERO_TO_ONE"
# )

# add_library(${project_name}::${project_name} ALIAS ${project_name})
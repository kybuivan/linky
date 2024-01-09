add_executable(linky_core_tests)

target_sources(linky_core_tests
    PRIVATE
        test_main.cpp
        test_version.cpp
)

#add_subdirectory(base)
#add_subdirectory(conformance)
add_subdirectory(concurrency)
add_subdirectory(profiler)
add_subdirectory(math)
add_subdirectory(parser)
add_subdirectory(reflection)
add_subdirectory(serialization)

get_target_property(SOURCES_FILES linky_core_tests SOURCES)
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCES_FILES})

include(catch)
target_link_libraries(linky_core_tests
    PRIVATE
        linky::core
        external::catch
)

include(CTest)
include(ParseAndAddCatchTests)
set(PARSE_CATCH_TESTS_ADD_TARGET_IN_TEST_NAME Off)
ParseAndAddCatchTests(linky_core_tests)
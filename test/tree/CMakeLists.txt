add_executable (tree_tests "tests.cc")
target_include_directories (tree_tests PRIVATE ${include_dir})
target_link_libraries (tree_tests gtest_main)
add_test(tree_tests ${TEST_RUNTIME_OUTPUT_DIRECTORY}/tree_tests)

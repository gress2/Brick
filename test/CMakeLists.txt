add_executable (tree_tests "tree_tests.cc")
target_include_directories (tree_tests PRIVATE ${include_dir})
target_link_libraries (tree_tests gtest_main)

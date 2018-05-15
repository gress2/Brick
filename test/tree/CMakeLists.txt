add_executable (unit_tests "unit_tests.cc")
target_include_directories (unit_tests PRIVATE ${include_dir})
target_link_libraries (unit_tests gtest_main)

add_executable (io_tests "io.cc")

target_include_directories (io_tests PRIVATE ${include_dir})
target_include_directories (io_tests PRIVATE ${test_include_dir})
target_link_libraries (io_tests gtest_main)

add_test (io_tests ${TEST_RUNTIME_OUTPUT_DIRECTORY}/io_tests ${test_data_dir})

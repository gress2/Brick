add_executable (io_tests "io.cc" ${antlr4cpp_src_files_brick})
add_dependencies (io_tests antlr4cpp antlr4cpp_generation_brick)

target_include_directories (io_tests PRIVATE ${include_dir})
target_include_directories (io_tests PRIVATE ${test_include_dir})
target_link_libraries (io_tests gtest_main antlr4-runtime)

add_test (io_tests ${TEST_RUNTIME_OUTPUT_DIRECTORY}/io_tests ${test_data_dir})

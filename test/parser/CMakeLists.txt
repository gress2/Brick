add_executable (parser_tests parser.cc ${antlr4cpp_src_files_brick})
add_dependencies (parser_tests antlr4cpp antlr4cpp_generation_brick)

target_include_directories (parser_tests PRIVATE ${include_dir})
target_link_libraries (parser_tests gtest_main)
target_link_libraries (parser_tests antlr4-runtime)

add_test (parser_tests ${TEST_RUNTIME_OUTPUT_DIRECTORY}/parser_tests)

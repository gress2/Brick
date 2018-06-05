add_executable (AST_tests AST.cc ${antlr4cpp_src_files_brick})
add_executable (parse_tests parse.cc ${antlr4cpp_src_files_brick})

add_dependencies (AST_tests antlr4cpp antlr4cpp_generation_brick)
add_dependencies (parse_tests antlr4cpp antlr4cpp_generation_brick)

target_include_directories (AST_tests PRIVATE ${include_dir})
target_include_directories (parse_tests PRIVATE ${include_dir})

target_link_libraries (AST_tests gtest_main antlr4-runtime)
target_link_libraries (parse_tests gtest_main antlr4-runtime)

add_test (AST_tests ${TEST_RUNTIME_OUTPUT_DIRECTORY}/AST_tests)
add_test (parse_tests ${TEST_RUNTIME_OUTPUT_DIRECTORY}/parse_tests)

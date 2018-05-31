add_executable (transformer "transformer.cc" ${antlr4cpp_src_files_brick})
add_dependencies (transformer antlr4cpp antlr4cpp_generation_brick)
target_include_directories (transformer PRIVATE ${include_dir})
target_link_libraries (transformer antlr4-runtime)

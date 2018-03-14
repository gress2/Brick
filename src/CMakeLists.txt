add_executable (parser "parser.cc")
add_executable (transformer "transformer.cc")
target_include_directories (parser PRIVATE ${include_dir})
target_include_directories (transformer PRIVATE ${include_dir})

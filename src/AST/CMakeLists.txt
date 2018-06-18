add_library(brick_math
  ${grammar_dependencies}
)

add_dependencies (brick_math antlr4cpp antlr4cpp_generation_brick)

target_link_libraries (brick_math antlr4-runtime)

target_include_directories (brick_math SYSTEM INTERFACE
  ${ANTLR4CPP_INCLUDE_DIRS}
  ${antlr4cpp_include_dirs_brick}
)

add_library(brick_ast
  AST_builder.cc
  AST.cc
  bfs_iterator.cc
  dfs_iterator.cc
  iterator.cc
  node.cc
  parse.cc
)

add_dependencies (brick_ast brick_utils brick_math)

target_link_libraries (brick_ast brick_utils brick_math)

target_include_directories (brick_ast SYSTEM INTERFACE 
  ${include_dir} 
)

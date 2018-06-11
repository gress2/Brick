add_library(brick_ast
  AST_builder.cc
  AST.cc
  dfs_iterator.cc
  iterator.cc
  node.cc
  parse.cc
)

add_dependencies (brick_ast antlr4cpp antlr4cpp_generation_brick)

target_link_libraries (brick_ast brick_utils)

target_include_directories (brick_ast PRIVATE ${include_dir})
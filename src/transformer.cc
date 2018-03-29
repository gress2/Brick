#include <iostream>

#include "brick.hpp"
#include "cxxopts.hpp"

int main() {
    cxxopts::Options options("Transformer", "Find potential AST transformations.");
    options.add_options()
      ("input", "Path to an AST file to be transformed")
    ;    

    Brick::AST::Reader reader("shit.ast");

    Brick::AST::AST ast = reader.read();
    ast.print();

    Brick::TreeBase::TreeBase tree_base;
    Brick::Transformer::Transformer transformer(ast, tree_base);
}

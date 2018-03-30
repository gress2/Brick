#include <iostream>

#include "brick.hpp"
#include "cxxopts.hpp"

int main(int argc, const char** argv) {

    cxxopts::Options options("Transformer", "Find potential AST transformations.");
    options.add_options()
      ("input", "Path to an AST file to be transformed", cxxopts::value<std::string>())
    ;
    auto args = options.parse(argc, argv);
    std::string input_file = args["input"].as<std::string>();

    Brick::AST::Reader reader(input_file);

    Brick::AST::Tree tree = reader.read();
    tree.print();

    Brick::TreeBase::TreeBase tree_base;
    Brick::Transformer::Transformer transformer(tree, tree_base);
}

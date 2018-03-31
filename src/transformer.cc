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

    brick::AST::tree<std::string> tree(nullptr, std::string{""});

    brick::tree_base::tree_base tree_base;
    brick::transformer::transformer<decltype(tree), decltype(tree_base)> transformer(tree, tree_base);
}

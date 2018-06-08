#ifndef BRICK_AST_PARSE_HPP_
#define BRICK_AST_PARSE_HPP_

#include "antlr4-runtime.h"
#include "MathLexer.h"
#include "MathParser.h"
#include "AST/AST_builder.hpp"
#include "AST/AST.hpp"

namespace brick::AST
{
  std::unique_ptr<brick::AST::AST> parse(std::istream& stream) {
    antlr4::ANTLRInputStream input(stream);
    brick::MathLexer lexer(&input); 
    antlr4::CommonTokenStream tokens(&lexer);
    brick::MathParser parser(&tokens);
    antlr4::tree::ParseTree *tree = parser.math();
    brick::AST::AST_builder builder;
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(&builder, tree);
    return builder.build();
  }

  std::unique_ptr<brick::AST::AST> parse(std::string math_str) {
    std::stringstream stream;
    stream << math_str << std::endl;
    return parse(stream);
  }
}

#endif

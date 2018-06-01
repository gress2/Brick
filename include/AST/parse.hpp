#ifndef BRICK_AST_PARSE_HPP_
#define BRICK_AST_PARSE_HPP_

#include "antlr4-runtime.h"
#include "MathLexer.h"
#include "MathParser.h"
#include "AST/ast_builder.hpp"
#include "tree/tree2.hpp"

namespace brick::AST
{
  brick::tree::tree2* parse(std::istream& stream) {
    antlr4::ANTLRInputStream input(stream);
    brick::MathLexer lexer(&input); 
    antlr4::CommonTokenStream tokens(&lexer);
    brick::MathParser parser(&tokens);
    antlr4::tree::ParseTree *tree = parser.math();
    brick::AST::ast_builder builder;
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(&builder, tree);
    return builder.build();
  }
}

#endif

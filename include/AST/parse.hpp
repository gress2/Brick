#pragma once

#include "antlr4-runtime.h"
#include "MathLexer.h"
#include "MathParser.h"
#include "AST/AST_builder.hpp"
#include "AST/AST.hpp"

namespace brick::AST
{
  std::unique_ptr<brick::AST::AST> parse(std::istream&);
  std::unique_ptr<brick::AST::AST> parse(std::string);
}

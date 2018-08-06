#pragma once

#include "AST/AST.hpp"
#include "AST/AST_builder.hpp"
#include "AST/parse.hpp"

// for whatever reason, the antlr runtime undefines EOF...
#ifndef EOF
#define EOF (-1)
#endif

namespace Brick {}

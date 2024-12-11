#pragma once

#include "Tokenizer/Tokenizer.hpp"
#include "AST.hpp"

ASTNodeList BuildAST(TokenList tokens);

void ExecAST(const ASTNodeList& l, Stack& s);
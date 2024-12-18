#pragma once

#include "Tokenizer/Tokenizer.hpp"
#include "AST.hpp"

using ASTDictLiteralInfo = std::map<std::string, std::shared_ptr<ASTNode>>;

ASTNodeList BuildAST(TokenList tokens);

void ExecAST(const ASTNodeList& l, Stack& s);
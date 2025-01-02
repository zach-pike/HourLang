#pragma once

#include "Tokenizer/Tokenizer.hpp"
#include "AST.hpp"

#include <string>
#include <vector>

using ASTDictLiteralInfo = std::map<std::string, std::shared_ptr<ASTNode>>;

ASTNodeList BuildAST(TokenList tokens);

void ExecAST(const ASTNodeList& l, Stack& s);
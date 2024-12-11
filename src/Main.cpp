#include "Utility/ReadFile.hpp"

#include "Tokenizer/Tokenizer.hpp"
#include "AST/AST.hpp"
#include "Stack/Stack.hpp"

#include "AST/ASTBuilder.hpp"
#include "Globals/Globals.hpp"

#include <iostream>

int main(int argc, char** argv) {
    // Get text code
    std::string fileCode = ReadFile("examples/test.hc");

    // Tokenize the code
    TokenList tokens = Tokenizer(fileCode);

    // for (auto token : tokens) {
    //     std::cout <<tokenNames[(int) token.type] << '\n';
    // }

    ASTNodeList prgm = buildAST(tokens);

    // Exec ast
    Stack stack;

    InitGlobals(stack);

    for (auto& n : prgm) {
        // n->printDebug();
        n->getValue(stack);
    }

    return 0;
}
#include "Interpreter.hpp"

#include "Tokenizer/Tokenizer.hpp"
#include "AST/ASTBuilder.hpp"
#include "Globals/Globals.hpp"

#include "Utility/ReadTextFile.hpp"

HourInterpreter::HourInterpreter() {}
HourInterpreter::~HourInterpreter() {}

void HourInterpreter::setDebugLevel(int dbg) {
    level = dbg;
}

void HourInterpreter::addGlobals() {
    InitGlobals(stack);
}

void HourInterpreter::reset() {
    stack = Stack();
}

Stack& HourInterpreter::getStack() {
    return stack;
}

void HourInterpreter::execCode(std::string code) {
    TokenList tokens = Tokenizer(code);

    if (level >= 1) {
        std::cout << "---------- TOKEN LIST ----------\n";
        for (auto token : tokens) {
            std::cout << tokenNames[(int) token.type];

            if (token.type == TokenType::LITERAL) {
                std::cout << ' ' << std::any_cast<std::string>(token.associatedData);
            }

            std::cout << '\n';
        }
        std::cout << "---------- END TOKEN LIST ----------\n\n";

        return;
    }

    ASTNodeList prgm;

    try {
        prgm = BuildAST(tokens);
    } catch(std::exception& e) {
        std::cout << "Exception thrown in AST Build!\n"
                  << e.what() << '\n';
    }

    // Print ast
    if (level >= 2) {
        std::cout << "---------- AST Tree View ----------\n";

        for (auto& n : prgm) {
            n->printDebug();
        }

        std::cout << "---------- END AST Tree View ----------\n";

        return;
    }

    ExecAST(prgm, stack);
}

void HourInterpreter::execFile(std::filesystem::path path)  {
    std::string fileCode = ReadTextFile(path);

    execCode(fileCode);
}
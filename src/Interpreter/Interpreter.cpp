#include "Interpreter.hpp"

#include "Tokenizer/Tokenizer.hpp"
#include "AST/ASTBuilder.hpp"
#include "Globals/Globals.hpp"

#include "Utility/ReadFile.hpp"

HourInterpreter::HourInterpreter() {}
HourInterpreter::~HourInterpreter() {}

void HourInterpreter::addGlobals() {
    InitGlobals(stack);
}

void HourInterpreter::execCode(std::string code) {
    TokenList tokens = Tokenizer(code);
    ASTNodeList prgm = BuildAST(tokens);
    ExecAST(prgm, stack);
}

void HourInterpreter::execFile(std::filesystem::path path)  {
    std::string fileCode = ReadFile(path);

    execCode(fileCode);
}
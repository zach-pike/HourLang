#include "Interpreter.hpp"

#include "Tokenizer/Tokenizer.hpp"
#include "AST/ASTBuilder.hpp"
#include "Globals/Globals.hpp"

#include "Utility/ReadFile.hpp"

HourInterpreter::HourInterpreter() {}
HourInterpreter::~HourInterpreter() {}

void HourInterpreter::addGlobals(PrintFunction pf, NewlineFunction nf) {
    InitGlobals(stack, pf, nf);
}

void HourInterpreter::reset() {
    stack = Stack();
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
#pragma once

#include <string>
#include <filesystem>

#include "AST/AST.hpp"
#include "Stack/Stack.hpp"

class HourInterpreter {
private:
    Stack stack;

    int level;
public:
    HourInterpreter();
    ~HourInterpreter();

    void setDebugLevel(int level);

    void addGlobals(PrintFunction pf, NewlineFunction nf);
    void reset();

    Stack& getStack();

    void execCode(std::string code);
    void execFile(std::filesystem::path path);
};
#pragma once

#include <string>
#include <filesystem>

#include "AST/AST.hpp"
#include "Stack/Stack.hpp"

class HourInterpreter {
private:
    Stack stack;
public:
    HourInterpreter();
    ~HourInterpreter();

    void addGlobals();

    void execCode(std::string code);
    void execFile(std::filesystem::path path);
};
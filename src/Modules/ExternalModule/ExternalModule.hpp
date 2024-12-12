#pragma once
#include "Types.hpp"

#include <string>
#include <vector>
#include <functional>

#include "Stack/Function/Function.hpp"

struct ModuleFunction {
    std::string symbolName;
    std::string functionName;
    ExternalFunctionParameterInformation paramInfo;
};

using ModuleFunctionList = std::vector<ModuleFunction>;

extern "C" {
    void moduleMain(Stack&);
    ModuleFunctionList getModuleFunctions();
}

using ModuleMainFunc = void(*)(Stack&);
using GetModuleFunctionsFunc = ModuleFunctionList(*)();
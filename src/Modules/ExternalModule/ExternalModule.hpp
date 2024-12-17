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

#define MODULE_EXPORT(functionList, functionName, symbolName, requiredParams) { \
    functionList.push_back( \
        ModuleFunction { \
            symbolName, \
            functionName, \
            ExternalFunctionParameterInformation { \
                requiredParams, \
                false \
            } \
        } \
    ); \
} 

#define PARAM_TYPES(v...) std::vector<VariableType>({ v })
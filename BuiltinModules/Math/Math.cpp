#pragma GCC push_options
#pragma GCC optimize("O0")

#include "Modules/ExternalModule/ExternalModule.hpp"
#include "Utility/Conv.hpp"

#include <iostream>
#include <cmath>


static int safe_mod(int a, int b) {
    return ((a % b) + b) % b;
}

extern "C" {
    std::any modFunc(Array params, Stack& s) {
        if (params[0].type() == typeid(float) || params[1].type() == typeid(float)) {
            float f1 = ConvToFloat(params[0]);
            float f2 = ConvToFloat(params[1]);

            return std::fmod(f1, f2);
        } else {
            int i1 = std::any_cast<int>(params[0]);
            int i2 =  std::any_cast<int>(params[1]);

            return safe_mod(i1, i2);
        }
    }

    std::any minFunc(Array params, Stack& s) {
        if (params[0].type() == typeid(float) || params[1].type() == typeid(float)) {
            float f1 = ConvToFloat(params[0]);
            float f2 = ConvToFloat(params[1]);

            return std::min(f1, f2);
        } else {
            int i1 = std::any_cast<int>(params[0]);
            int i2 =  std::any_cast<int>(params[1]);

            return std::min(i1, i2);
        }
    }

    std::any maxFunc(Array params, Stack& s) {
        if (params[0].type() == typeid(float) || params[1].type() == typeid(float)) {
            float f1 = ConvToFloat(params[0]);
            float f2 = ConvToFloat(params[1]);

            return std::max(f1, f2);
        } else  {
            int i1 = std::any_cast<int>(params[0]);
            int i2 =  std::any_cast<int>(params[1]);
    
            return std::max(i1, i2); 
        }
    }

    std::any randIntFunc(Array params, Stack& s) {
        Int min = std::any_cast<Int>(params[0]);
        Int max = std::any_cast<Int>(params[1]);

        return (int)(min + rand() % (max - min + 1));
    }

    std::any randomFunc(Array params, Stack& s) {
        srand(time(nullptr));

        return (float)rand() / (float)INT_MAX;
    }

    void moduleMain(Stack& s) {
        // std::cout << "Math module initalized\n";
    }

    std::vector<ModuleFunction> getModuleFunctions() {
        // Module functions
        ModuleFunction mod{
            .symbolName = "modFunc",
            .functionName = "mod",
            .paramInfo = ExternalFunctionParameterInformation {
                .requiredVariableTypes = std::vector<VariableType>({ VariableType::INT | VariableType::FLOAT, VariableType::INT | VariableType::FLOAT }),
                .hasVaArgs = false
            }
        };

        ModuleFunction min{
            .symbolName = "minFunc",
            .functionName = "min",
            .paramInfo = ExternalFunctionParameterInformation {
                .requiredVariableTypes = std::vector<VariableType>({ VariableType::INT | VariableType::FLOAT, VariableType::INT | VariableType::FLOAT }),
                .hasVaArgs = false
            }
        };

        ModuleFunction max{
            .symbolName = "maxFunc",
            .functionName = "max",
            .paramInfo = ExternalFunctionParameterInformation {
                .requiredVariableTypes = std::vector<VariableType>({ VariableType::INT | VariableType::FLOAT, VariableType::INT | VariableType::FLOAT }),
                .hasVaArgs = false
            }
        };

        ModuleFunction randInt{
            .symbolName = "randIntFunc",
            .functionName = "randInt",
            .paramInfo = ExternalFunctionParameterInformation {
                .requiredVariableTypes = std::vector<VariableType>({ VariableType::INT, VariableType::INT }),
                .hasVaArgs = false
            }
        };

        ModuleFunction random{
            .symbolName = "randomFunc",
            .functionName = "random",
            .paramInfo = ExternalFunctionParameterInformation {
                .requiredVariableTypes = std::vector<VariableType>({}),
                .hasVaArgs = false
            }
        };

        std::vector<ModuleFunction> funcs;
        funcs.push_back(mod);
        funcs.push_back(min);
        funcs.push_back(max);
        funcs.push_back(randInt);
        funcs.push_back(random);
        
        return funcs;
    }
}

#pragma GCC pop_options
#pragma GCC push_options
#pragma GCC optimize("O0")

#include "Modules/ExternalModule/ExternalModule.hpp"
#include "Utility/Conv.hpp"

#include <iostream>
#include <cmath>
#include <random>

static int safe_mod(int a, int b) {
    return ((a % b) + b) % b;
}

static std::random_device randDev;
static std::mt19937 rng(randDev());

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

    std::any absFunc(Array params, Stack& s) {
        if (params[0].type() == typeid(Float)) {
            Float f = std::any_cast<Float>(params[0]);

            return std::fabs(f);
        } else if (params[0].type() == typeid(Int)) {
            Int f = std::any_cast<Int>(params[0]);

            return std::abs(f);
        }

        return std::any();
    }

    std::any sqrtFunc(Array params, Stack& s) {
        if (params[0].type() == typeid(Float)) {
            Float f = std::any_cast<Float>(params[0]);

            return std::sqrtf(f);
        } else if (params[0].type() == typeid(Int)) {
            Int f = std::any_cast<Int>(params[0]);

            return (Int) std::sqrt(f);
        }

        return std::any();
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

        std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

        return (Int) dist(rng);
    }

    std::any randomFunc(Array params, Stack& s) {
        std::uniform_real_distribution<> dist(0.0, 1.0);

        return (Float) dist(rng);
    }

    void moduleMain(Stack& s) {}

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

        ModuleFunction abs{
            .symbolName = "absFunc",
            .functionName = "abs",
            .paramInfo = ExternalFunctionParameterInformation {
                .requiredVariableTypes = std::vector<VariableType>({ VariableType::INT | VariableType::FLOAT }),
                .hasVaArgs = false
            }
        };

        ModuleFunction sqrt{
            .symbolName = "sqrtFunc",
            .functionName = "sqrt",
            .paramInfo = ExternalFunctionParameterInformation {
                .requiredVariableTypes = std::vector<VariableType>({ VariableType::INT | VariableType::FLOAT }),
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
        funcs.push_back(abs);
        funcs.push_back(min);
        funcs.push_back(max);
        funcs.push_back(randInt);
        funcs.push_back(sqrt);
        funcs.push_back(random);
        
        return funcs;
    }
}

#pragma GCC pop_options
#include "Function.hpp"
#include "Exceptions/Exceptions.hpp"
#include "Stack/Stack.hpp"

#include <exception>
#include <stdexcept>
#include <cstring>
#include <assert.h>

Function::Function(InternalFunction f, ParameterNameList p):
    func(f),
    parameters(p) {}

Function::Function(ExternalFunction f, ExternalFunctionParameterInformation p):
    func(f),
    parameters(p) {}

static VariableType getVarType(std::any a) {
    if (a.type() == typeid(Int)) {
        return VariableType::INT;
    } else if (a.type() == typeid(Float)) {
        return VariableType::FLOAT;
    } else if (a.type() == typeid(Bool)) {
        return VariableType::BOOL;
    } else if (a.type() == typeid(String)) {
        return VariableType::STRING;
    } else if (a.type() == typeid(Array)) {
        return VariableType::ARRAY;
    } else if(a.type() == typeid(Dict)) {
        return VariableType::DICT;
    } else {
        throw std::runtime_error("Unknown datatype");
    }
}

std::any Function::callFunction(ParameterValueList parameterValues, Stack& stack) {
    if (std::holds_alternative<InternalFunction>(func)) {
        auto params = std::get<ParameterNameList>(parameters);

        assert(parameterValues.size() == params.size());
        stack.clearReturnValue();

        stack.pushScope();

        // Push parameters here
        for (int i=0; i < params.size(); i++) {
            stack.setVariable(params[i], parameterValues[i]);
        }

        std::get<InternalFunction>(func)->getValue(stack);

        stack.popScope();

        return stack.getReturnValue();

    } else if (std::holds_alternative<ExternalFunction>(func)) {
        ExternalFunctionParameterInformation info = std::get<ExternalFunctionParameterInformation>(parameters);

        Array argsList;

        // Try and get all required args
        if (parameterValues.size() < info.requiredVariableTypes.size()) throw InvalidParameterCount(info.requiredVariableTypes.size());

        argsList.insert(argsList.end(), parameterValues.begin(), parameterValues.begin() + info.requiredVariableTypes.size());

        // Verify types
        for (int i=0; i<info.requiredVariableTypes.size(); i++) {
            VariableType vt = info.requiredVariableTypes[i];
        
            if (vt != VariableType::ANY && !(getVarType(argsList[i]) & vt)) {
                throw InvalidParameterType(vt, getVarType(argsList[i]));
            }
        }

        std::size_t vaStartPos = info.requiredVariableTypes.size();

        if (info.hasVaArgs) {
            // Try and get variadic args
            assert(parameterValues.size() - vaStartPos >= info.minVaArgs);
            assert(parameterValues.size() - vaStartPos < info.maxVaArgs);

            argsList.push_back(Array(parameterValues.begin() + vaStartPos, parameterValues.end()));

            // Verify
            if (info.vaType != VariableType::ANY) {
                const auto& vaArgsList = std::any_cast<Array>(argsList.back());

                for (int i=0; i<vaArgsList.size(); i++) {
                    if (!(info.vaType & getVarType(vaArgsList[i]))) {
                        throw InvalidParameterType(info.vaType, getVarType(vaArgsList[i]));
                    } 
                }
            }
        }

        return std::get<ExternalFunction>(func)(argsList, stack);
    }

    throw std::runtime_error("Invalid function type");
}
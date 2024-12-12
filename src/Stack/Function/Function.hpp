#pragma once

#include "AST/AST.hpp"

#include <variant>
#include <functional>

#include "Types.hpp"

class Stack;

using InternalFunction = std::shared_ptr<ASTNode>;

using ParameterValueList = Array;
using ParameterNameList = std::vector<std::string>;
using ExternalFunction = std::function<std::any(ParameterValueList, Stack&)>;

struct ExternalParameterInformation {
    std::vector<VariableType> requiredVariableTypes;

    bool hasVaArgs;
    std::size_t minVaArgs;
    std::size_t maxVaArgs;
    VariableType vaType;
};

class Function {
private:
    std::variant<InternalFunction, ExternalFunction> func;
    std::variant<ParameterNameList,  ExternalParameterInformation> parameters;

public:
    Function(InternalFunction f, ParameterNameList p);
    Function(ExternalFunction f, ExternalParameterInformation p);

    std::any callFunction(ParameterValueList parameterValues, Stack& stack);
};
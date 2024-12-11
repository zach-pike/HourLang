#pragma once

#include "AST/AST.hpp"

#include <variant>
#include <functional>

class Stack;

using InternalFunction = std::shared_ptr<ASTNode>;

using ParameterValueList = std::vector<std::any>;
using ParameterNameList = std::vector<std::string>;
using ExternalFunction = std::function<std::any(ParameterValueList, ParameterNameList)>;

class Function {
private:
    std::variant<InternalFunction, ExternalFunction> func;
    ParameterNameList parameters;

public:
    Function(InternalFunction f, ParameterNameList p);
    Function(ExternalFunction f, ParameterNameList p);

    std::any callFunction(std::vector<std::any> parameterValues, Stack& stack);
};
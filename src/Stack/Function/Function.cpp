#include "Function.hpp"

#include "Stack/Stack.hpp"

#include <exception>
#include <stdexcept>

#include <assert.h>

Function::Function(InternalFunction f, ParameterNameList p):
    func(f),
    parameters(p) {}

Function::Function(ExternalFunction f, ParameterNameList p):
    func(f),
    parameters(p) {}

// Function(const Function& other)
    //     : func(other.func), parameters(other.parameters) {}

std::any Function::callFunction(std::vector<std::any> parameterValues, Stack& stack) {
    if (std::holds_alternative<InternalFunction>(func)) {
        assert(parameterValues.size() == parameters.size());
        stack.clearReturnValue();

        stack.pushScope();

        // Push parameters here
        for (int i=0; i < parameters.size(); i++) {
            stack.setVariable(parameters[i], parameterValues[i]);
        }

        std::get<InternalFunction>(func)->getValue(stack);

        stack.popScope();

        return stack.getReturnValue();

    } else if (std::holds_alternative<ExternalFunction>(func)) {
        return std::get<ExternalFunction>(func)(parameterValues, parameters, stack);
    }

    throw std::runtime_error("Invalid function type");
}
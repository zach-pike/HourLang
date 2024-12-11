#pragma once

#include "Scope/Scope.hpp"

#include <queue>

class Stack {
private:
    std::vector<Scope> scopes;
    std::any returnValue;

public:
    Stack();
    ~Stack();

    void pushScope();
    void popScope();

    std::optional<std::any> getVariable(std::string name) const;
    std::optional<std::shared_ptr<Function>> getFunction(std::string name) const;

    void setVariable(std::string name, std::any value);
    void setFunction(std::string name, std::shared_ptr<Function> f);

    void setReturnValue(std::any returnValue);
    void clearReturnValue();
    std::any getReturnValue() const;
};
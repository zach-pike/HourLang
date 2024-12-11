#pragma once

#include "Stack/Function/Function.hpp"

#include <map>
#include <string>
#include <any>
#include <optional>

class Scope {
private:
    std::map<std::string, std::any> scopeVariables;
    std::map<std::string, std::shared_ptr<Function>> scopeFunctions;
public:
    Scope();
    ~Scope();

    std::optional<std::any> getVariable(std::string name) const;
    std::optional<std::shared_ptr<Function>> getFunction(std::string name) const;

    void setVariable(std::string name, std::any value);
    void setFunction(std::string name, std::shared_ptr<Function> f);
};
#include "Scope.hpp"

Scope::Scope() {}
Scope::~Scope() {}

std::optional<std::any> Scope::getVariable(std::string name) const {
    auto k = scopeVariables.find(name);

    if (k != scopeVariables.end())
        return k->second;

    return std::nullopt;
}

std::optional<std::shared_ptr<Function>> Scope::getFunction(std::string name) const {
    auto k = scopeFunctions.find(name);

    if (k != scopeFunctions.end())
        return k->second;

    return std::nullopt;
}

void Scope::setVariable(std::string name, std::any value) {
    scopeVariables[name] = value;
}

void Scope::setFunction(std::string name, std::shared_ptr<Function> f) {
    scopeFunctions[name] = f;
}
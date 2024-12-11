#include "Stack.hpp"

#include <iostream>

Stack::Stack() {
    // Global scope
    scopes.push_back(Scope());
}

Stack::~Stack() {}

void Stack::pushScope() {
    scopes.push_back(Scope());
}

void Stack::popScope() {
    scopes.pop_back();
}

std::optional<std::any> Stack::getVariable(std::string name) const {
    for (auto i=scopes.end()-1; i >= scopes.begin(); i --) {
        auto a = i->getVariable(name);

        if (a.has_value())
            return a.value();
    }

    return std::nullopt;
}

std::optional<std::shared_ptr<Function>> Stack::getFunction(std::string name) const {
    for (auto i=scopes.end()-1; i >= scopes.begin(); i --) {
        auto a = i->getFunction(name);

        if (a.has_value())
            return a.value();
    }

    return std::nullopt;
}

void Stack::setVariable(std::string name, std::any value) {
    // try to find a scope with this variable already defined
    std::vector<Scope>::iterator i = scopes.end() - 1;
    for (; i >= scopes.begin(); i--) {
        if (i->getVariable(name).has_value()) {
            i->setVariable(name, value);
            return;
        }
    }

    scopes.back().setVariable(name, value);
}

void Stack::setFunction(std::string name, std::shared_ptr<Function> f) {
    scopes.back().setFunction(name, f);
}

void Stack::setReturnValue(std::any _returnValue) {
    returnValue = _returnValue;
}

void Stack::clearReturnValue() {
    returnValue = std::any();
}

std::any Stack::getReturnValue() const {
    return returnValue;
}
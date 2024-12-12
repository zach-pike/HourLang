#pragma once

#include "Scope/Scope.hpp"
#include "Modules/LoadedModule.hpp"

#include <vector>
#include <any>
#include <filesystem>

class Stack {
private:
    std::vector<Scope> scopes;
    std::any returnValue;

    std::vector<std::filesystem::path> moduleSearchPaths;
    std::vector<LoadedModule> loadedModules;
public:
    Stack();
    ~Stack();

    void pushScope();
    void popScope();

    std::optional<std::any> getVariable(std::string name) const;
    std::optional<std::shared_ptr<Function>> getFunction(std::string name) const;

    void setVariable(std::string name, std::any value);
    void setFunction(std::string name, std::shared_ptr<Function> f);

    void import(std::string name);
    void addModulePath(std::filesystem::path path);

    void setReturnValue(std::any returnValue);
    void clearReturnValue();
    std::any getReturnValue() const;
};
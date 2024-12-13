#include "Stack.hpp"
#include "Modules/ExternalModule/ExternalModule.hpp"
#include "Exceptions/Exceptions.hpp"
#include "Utility/ReadTextFile.hpp"
#include "AST/ASTBuilder.hpp"


#include <iostream>
#include <assert.h>
#include <windows.h>

Stack::Stack() {
    // Global scope
    scopes.push_back(Scope());
}

Stack::~Stack() {
    // Unload open modules
    for (auto mod : loadedModules) {
        FreeLibrary((HMODULE) mod.libraryHandle);
    }
}

void Stack::pushScope() {
    scopes.push_back(Scope());
}

void Stack::popScope() {
    scopes.pop_back();
}

void Stack::import(std::string name) {
    // Try and find the file we need
    bool foundModule = false;
    std::filesystem::path modulePath;
    for (auto& searchPath : moduleSearchPaths) {
        if (!std::filesystem::is_directory(searchPath)) throw std::runtime_error(searchPath.string() + " is not a directory!");

        for (auto item : std::filesystem::directory_iterator(searchPath)) {
            if (item.is_directory()) continue;

            if (item.path().stem() == name) {
                foundModule = true;
                modulePath = item.path();
                break;
            }
        }

        if (foundModule) break;
    }

    if (!foundModule) throw ModuleNotFound(name);

    std::string modulePathStr = modulePath.u8string();
    
    if (modulePath.extension() == "dll") {
        HMODULE library = LoadLibrary(modulePathStr.c_str());

        ModuleMainFunc moduleMain = (ModuleMainFunc)GetProcAddress(library, "moduleMain");
        GetModuleFunctionsFunc functions = (GetModuleFunctionsFunc) GetProcAddress(library, "getModuleFunctions");

        // Initialize Module 
        // Call module main
        moduleMain(*this);

        // Next load the list of functions
        ModuleFunctionList info = functions();

        for (auto& func : info) {
            void* f = (void*) GetProcAddress(library, func.symbolName.c_str());

            if (f == nullptr) {
                throw std::runtime_error("Could not load function \"" + func.symbolName + "\"");
            }

            setFunction(
                func.functionName,
                std::make_shared<Function>(
                    (std::any(*)(ParameterValueList, Stack&)) f,
                    func.paramInfo
                )    
            );
        }

        loadedModules.push_back(
            LoadedModule{
                .moduleName = name,
                .loadedFunctions = info,
                .libraryHandle = (void*) library
            }
        );
    } else {
        // Try and read as text and exec file
        std::string text = ReadTextFile(modulePathStr);
        TokenList tokens = Tokenizer(text);
        ASTNodeList nodes = BuildAST(tokens);

        ExecAST(nodes, *this);
    }
}

void Stack::addModulePath(std::filesystem::path path) {
    moduleSearchPaths.push_back(path);
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
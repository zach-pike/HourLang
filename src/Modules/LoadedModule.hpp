#pragma once

#include "ExternalModule/ExternalModule.hpp"

struct LoadedModule {
    std::string moduleName;
    std::vector<ModuleFunction> loadedFunctions;
    void* libraryHandle;
};
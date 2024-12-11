#include "Globals.hpp"

#include <any>
#include <vector>
#include <iostream>

#include "Utility/Conv.hpp"
#include "Utility/GetVarTypeString.hpp"

std::any printFunc(std::vector<std::any> params, std::vector<std::string> paramNames) {
    std::cout << ConvToString(params[0]) << '\n';
    return std::any();
}

std::any typeFunc(std::vector<std::any> params, std::vector<std::string> paramNames) {
    return std::string(GetVarTypeString(params[0]));
}

void InitGlobals(Stack& s) {
    std::vector<std::string> oneParam = { "a" };

    s.setFunction("print", std::make_shared<Function>(printFunc, oneParam));
    s.setFunction("type", std::make_shared<Function>(typeFunc, oneParam));
}
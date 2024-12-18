#include "GetVarTypeString.hpp"

#include <string>
#include <iostream>
#include <vector>

#include "Types.hpp"

const char* GetVarTypeString(std::any v) {
    if (v.type() == typeid(int)) {
        return "int";
    } else if (v.type() == typeid(float)) {
        return "float";
    } else if (v.type() == typeid(bool)) {
        return "bool";
    } else if (v.type() == typeid(std::string)) {
        return "string";
    } else if (v.type() == typeid(Array)) {
        return "array";
    } else if (v.type() == typeid(Dict)) {
        return "dict";
    }

    return "null";
}
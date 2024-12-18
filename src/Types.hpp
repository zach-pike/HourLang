#pragma once

#include <vector>
#include <any>
#include <functional>
#include <cstdint>
#include <string>
#include <map>

#define ARR_SZ(a) (sizeof(a)/sizeof(a[0]))

enum class VariableType : std::uint16_t {
    ANY = 0,
    INT = 1,
    FLOAT = 2,
    BOOL = 4,
    STRING = 8,
    ARRAY = 16,
    DICT = 32,
};

constexpr VariableType variableTypeOptions[] = {
    VariableType::ANY,
    VariableType::INT,
    VariableType::FLOAT,
    VariableType::BOOL,
    VariableType::STRING,
    VariableType::ARRAY,
    VariableType::DICT,
};

constexpr const char* variableTypeNames[] = {
    "Any",
    "Int",
    "Float",
    "Bool",
    "String",
    "Array",
    "Dict",
};

inline VariableType operator|(VariableType lhs, VariableType rhs) {
    return static_cast<VariableType>(
        static_cast<unsigned int>(lhs) | static_cast<unsigned int>(rhs));
}

inline bool operator&(VariableType lhs, VariableType rhs) {
    return static_cast<bool>(
        static_cast<unsigned int>(lhs) & static_cast<unsigned int>(rhs));
}

using Any = std::any;
using Int = int;
using Float = float;
using Bool = bool;
using String = std::string;
using Array = std::vector<Any>;
using Dict = std::map<String, Any>; 



using PrintFunction = std::function<void(std::string)>;
using NewlineFunction = std::function<void()>;
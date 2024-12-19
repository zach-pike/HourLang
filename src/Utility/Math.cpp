#include "Math.hpp"

#include "Conv.hpp"
#include "GetVarTypeString.hpp"

#include <string>
#include <stdexcept>
#include <exception>

#include "Types.hpp"

Any Add(Any lhs, Any rhs) {
    if (lhs.type() == typeid(String) || rhs.type() == typeid(String)) {
        String s1 = ConvToString(lhs);
        String s2 = ConvToString(rhs);

        return s1 + s2;
    } else if (lhs.type() == typeid(Float) || rhs.type() == typeid(Float)) {
        Float f1 = ConvToFloat(lhs);
        Float f2 = ConvToFloat(rhs);

        return f1 + f2;
    } else if (lhs.type() == typeid(Int) || rhs.type() == typeid(Int)) {
        Int i1 = ConvToInt(lhs);
        Int i2 = ConvToInt(rhs);

        return i1 + i2;
    } else if (lhs.type() == typeid(Array) && rhs.type() == typeid(Array)) {
        // Combine arrays
        auto a = std::any_cast<Array>(lhs);
        auto b = std::any_cast<Array>(rhs);

        a.insert(a.end(), b.begin(), b.end());

        return a;
    } else if (lhs.type() == typeid(Dict) && rhs.type() == typeid(Dict)) {
        // Combine dicts
        auto a = std::any_cast<Dict>(lhs);
        auto b = std::any_cast<Dict>(rhs);

        a.insert(b.begin(), b.end());

        return a;
    } else {
        // Only other type combo left is bool + bool
        bool b1 = std::any_cast<bool>(lhs);
        bool b2 = std::any_cast<bool>(rhs);

        return b1 || b2;
    }
}

Any Subtract(Any lhs, Any rhs) {
    if (lhs.type() == typeid(Float) || rhs.type() == typeid(Float)) {
        Float f1 = ConvToFloat(lhs);
        Float f2 = ConvToFloat(rhs);

        return f1 - f2;
    } else if (lhs.type() == typeid(Int) && rhs.type() == typeid(Int)) {
        Int i1 = std::any_cast<Int>(lhs);
        Int i2 = std::any_cast<Int>(rhs);

        return i1 - i2;
    } else {
        throw std::runtime_error("Cannot Subtract with [" + std::string(GetVarTypeString(lhs))  + "] and [" + std::string(GetVarTypeString(rhs)) + "]");
    }
}

Any Multiply(Any lhs, Any rhs) {
    if (lhs.type() == typeid(Float) || rhs.type() == typeid(Float)) {
        Float f1 = ConvToFloat(lhs);
        Float f2 = ConvToFloat(rhs);

        return f1 * f2;
    } else if (lhs.type() == typeid(Int) && rhs.type() == typeid(Int)) {
        Int i1 = std::any_cast<Int>(lhs);
        Int i2 = std::any_cast<Int>(rhs);

        return i1 * i2;
    } else {
        throw std::runtime_error("Cannot Multiply with [" + std::string(GetVarTypeString(lhs))  + "] and [" + std::string(GetVarTypeString(rhs)) + "]");
    }
}

Any Divide(Any lhs, Any rhs) {
    if (lhs.type() == typeid(Float) || rhs.type() == typeid(Float)) {
        Float f1 = ConvToFloat(lhs);
        Float f2 = ConvToFloat(rhs);

        return f1 / f2;
    } else if (lhs.type() == typeid(Int) && rhs.type() == typeid(Int)) {
        Int i1 = std::any_cast<Int>(lhs);
        Int i2 = std::any_cast<Int>(rhs);

        return i1 / i2;
    } else {
        throw std::runtime_error("Cannot Divide with [" + std::string(GetVarTypeString(lhs))  + "] and [" + std::string(GetVarTypeString(rhs)) + "]");
    }
}
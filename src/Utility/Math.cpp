#include "Math.hpp"

#include "Conv.hpp"
#include "GetVarTypeString.hpp"

#include <string>
#include <stdexcept>
#include <exception>

std::any Add(std::any lhs, std::any rhs) {
    if (lhs.type() == typeid(std::string) || rhs.type() == typeid(std::string)) {
        std::string s1 = lhs.type() == typeid(std::string) ? std::any_cast<std::string>(lhs) : ConvToString(lhs);
        std::string s2 = rhs.type() == typeid(std::string) ? std::any_cast<std::string>(rhs) : ConvToString(rhs);

        return s1 + s2;
    } else if (lhs.type() == typeid(float) || rhs.type() == typeid(float)) {
        float f1 = lhs.type() == typeid(float) ? std::any_cast<float>(lhs) : ConvToFloat(lhs);
        float f2 = rhs.type() == typeid(float) ? std::any_cast<float>(rhs) : ConvToFloat(rhs);

        return f1 + f2;
    } else if (lhs.type() == typeid(int) || rhs.type() == typeid(int)) {
        int i1 = lhs.type() == typeid(int) ? std::any_cast<int>(lhs) : ConvToInt(lhs);
        int i2 = rhs.type() == typeid(int) ? std::any_cast<int>(rhs) : ConvToInt(rhs);

        return i1 + i2;
    } else {
        // Only other type combo left is bool + bool
        bool b1 = std::any_cast<bool>(lhs);
        bool b2 = std::any_cast<bool>(rhs);

        return b1 || b2;
    }
}

std::any Subtract(std::any lhs, std::any rhs) {
    if (lhs.type() == typeid(float) || rhs.type() == typeid(float)) {
        float f1 = lhs.type() == typeid(float) ? std::any_cast<float>(lhs) : ConvToFloat(lhs);
        float f2 = rhs.type() == typeid(float) ? std::any_cast<float>(rhs) : ConvToFloat(rhs);

        return f1 - f2;
    } else if (lhs.type() == typeid(int) && rhs.type() == typeid(int)) {
        int i1 = std::any_cast<int>(lhs);
        int i2 = std::any_cast<int>(rhs);

        return i1 - i2;
    } else {
        throw std::runtime_error("Cannot Subtract with [" + std::string(GetVarTypeString(lhs))  + "] and [" + std::string(GetVarTypeString(rhs)) + "]");
    }
}

std::any Multiply(std::any lhs, std::any rhs) {
    if (lhs.type() == typeid(float) || rhs.type() == typeid(float)) {
        float f1 = lhs.type() == typeid(float) ? std::any_cast<float>(lhs) : ConvToFloat(lhs);
        float f2 = rhs.type() == typeid(float) ? std::any_cast<float>(rhs) : ConvToFloat(rhs);

        return f1 * f2;
    } else if (lhs.type() == typeid(int) && rhs.type() == typeid(int)) {
        int i1 = std::any_cast<int>(lhs);
        int i2 = std::any_cast<int>(rhs);

        return i1 * i2;
    } else {
        throw std::runtime_error("Cannot Multiply with [" + std::string(GetVarTypeString(lhs))  + "] and [" + std::string(GetVarTypeString(rhs)) + "]");
    }
}

std::any Divide(std::any lhs, std::any rhs) {
    if (lhs.type() == typeid(float) || rhs.type() == typeid(float)) {
        float f1 = lhs.type() == typeid(float) ? std::any_cast<float>(lhs) : ConvToFloat(lhs);
        float f2 = rhs.type() == typeid(float) ? std::any_cast<float>(rhs) : ConvToFloat(rhs);

        return f1 / f2;
    } else if (lhs.type() == typeid(int) && rhs.type() == typeid(int)) {
        int i1 = std::any_cast<int>(lhs);
        int i2 = std::any_cast<int>(rhs);

        return i1 / i2;
    } else {
        throw std::runtime_error("Cannot Divide with [" + std::string(GetVarTypeString(lhs))  + "] and [" + std::string(GetVarTypeString(rhs)) + "]");
    }
}
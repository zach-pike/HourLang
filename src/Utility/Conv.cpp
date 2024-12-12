#include "Conv.hpp"

#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "Types.hpp"
#include "AST/AST.hpp"

std::string ConvToString(std::any v) {
    if (v.type() == typeid(int)) {
        return std::to_string(std::any_cast<int>(v));
    } else if (v.type() == typeid(float)) {
        return std::to_string(std::any_cast<float>(v));
    } else if (v.type() == typeid(bool)) {
        return std::any_cast<bool>(v) ? "true" : "false";
    } else if (v.type() == typeid(std::string)) {
        return std::any_cast<std::string>(v);
    } else if (v.type() == typeid(Array)) {
        auto a = std::any_cast<Array>(v);
        std::stringstream ss;
        ss << '[';

        for (int i=0; i<a.size(); i++) {
            ss << ConvToString(a[i]);
            
            if (i != a.size()-1) ss << ", ";
        }

        ss << ']';

        return ss.str();
    } else {
        return "null";
    }
}

float ConvToFloat(std::any v) {
    if (v.type() == typeid(int)) {
        return static_cast<float>(std::any_cast<int>(v));
    } else if (v.type() == typeid(float)) {
        return std::any_cast<float>(v);
    } else if (v.type() == typeid(bool)) {
        return static_cast<float>(std::any_cast<bool>(v));
    } else if (v.type() == typeid(std::string)) {
        return std::stof(std::any_cast<std::string>(v));
    }

    throw std::runtime_error("Can't convert type to float!");
}

int ConvToInt(std::any v) {
    if (v.type() == typeid(int)) {
        return std::any_cast<int>(v);
    } else if (v.type() == typeid(float)) {
        return static_cast<int>(std::any_cast<float>(v));
    } else if (v.type() == typeid(bool)) {
        return static_cast<int>(std::any_cast<bool>(v));
    } else if (v.type() == typeid(std::string)) {
        return std::stoi(std::any_cast<std::string>(v));
    }

    throw std::runtime_error("Can't convert type to float!");
}

bool ConvToBool(std::any v) {
    if (v.type() == typeid(int)) {
        return static_cast<bool>(std::any_cast<int>(v));
    } else if (v.type() == typeid(float)) {
        return static_cast<bool>(std::any_cast<float>(v));
    } else if (v.type() == typeid(bool)) {
        return std::any_cast<bool>(v);
    } else if (v.type() == typeid(std::string)) {
        return std::any_cast<std::string>(v) == "true";
    }

    throw std::runtime_error("Can't convert type to float!");
}
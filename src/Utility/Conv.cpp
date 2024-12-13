#include "Conv.hpp"

#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "Types.hpp"
#include "AST/AST.hpp"

String ConvToString(std::any v) {
    if (v.type() == typeid(Int)) {
        return std::to_string(std::any_cast<Int>(v));

    } else if (v.type() == typeid(Float)) {
        return std::to_string(std::any_cast<Float>(v));

    } else if (v.type() == typeid(Bool)) {
        return std::any_cast<Bool>(v) ? "true" : "false";

    } else if (v.type() == typeid(String)) {
        return std::any_cast<String>(v);

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

Float ConvToFloat(std::any v) {
    if (v.type() == typeid(Int)) {
        return static_cast<Float>(std::any_cast<Int>(v));

    } else if (v.type() == typeid(Float)) {
        return std::any_cast<Float>(v);

    } else if (v.type() == typeid(Bool)) {
        return static_cast<Float>(std::any_cast<Bool>(v) ? 1 : 0);

    } else if (v.type() == typeid(String)) {
        return std::stof(std::any_cast<String>(v));
    }

    throw std::runtime_error("Can't convert type to float!");
}

Int ConvToInt(std::any v) {
    if (v.type() == typeid(Int)) {
        return std::any_cast<Int>(v);

    } else if (v.type() == typeid(Float)) {
        return static_cast<Int>(std::any_cast<Float>(v));

    } else if (v.type() == typeid(Bool)) {
        return static_cast<Int>(std::any_cast<Bool>(v));

    } else if (v.type() == typeid(String)) {
        return std::stoi(std::any_cast<String>(v));
    }

    throw std::runtime_error("Can't convert type to int!");
}

Bool ConvToBool(std::any v) {
    if (v.type() == typeid(Int)) {
        return static_cast<Bool>(std::any_cast<Int>(v));
        
    } else if (v.type() == typeid(Float)) {
        return static_cast<Bool>(std::any_cast<Float>(v));

    } else if (v.type() == typeid(Bool)) {
        return std::any_cast<Bool>(v);

    } else if (v.type() == typeid(String)) {
        return std::any_cast<String>(v) == "true";
    }

    throw std::runtime_error("Can't convert type to bool!");
}
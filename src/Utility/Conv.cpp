#include "Conv.hpp"

#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "Types.hpp"
#include "AST/AST.hpp"

#include "Utility/MultiLineManager.hpp"

static void recurseObject(Any a, MultiLineManager& m) {
    if (a.type() == typeid(Array)) {
        m.addText("[");
        
        auto arr = std::any_cast<Array>(a);
        if (arr.size() > 0) m.addNewline();

        m.addIndentLevel();

        for (auto& b : arr) {
            m.insertIndent();
            recurseObject(b, m);

            m.addText(", ");
            m.addNewline();
        }

        m.removeIndentLevel();

        m.insertIndent();
        m.addText("]");
    } else if (a.type() == typeid(Dict)) {
        m.addText("{");

        auto dict = std::any_cast<Dict>(a);

        if (dict.size() > 0) m.addNewline();

        m.addIndentLevel();

        for (auto child : dict) {
            m.insertIndent();

            m.addText(child.first);
            m.addText(": ");
            recurseObject(child.second, m);

            m.addText(", ");
            m.addNewline();
        }

        m.removeIndentLevel();
        m.insertIndent();
        m.addText("}");
    } else if (a.type() == typeid(String)) {
        if (m.getIndentLevel() != 0) m.addText("\"");
        m.addText(std::any_cast<String>(a));
        if (m.getIndentLevel() != 0) m.addText("\"");
    } else if (a.type() == typeid(Int)) {
        m.addText(std::to_string(std::any_cast<Int>(a)));
    } else if (a.type() == typeid(Float)) {
        m.addText(std::to_string(std::any_cast<Float>(a)));
    } else if (a.type() == typeid(Bool)) {
        m.addText(std::any_cast<Bool>(a) ? "true" : "false");
    } else {
        throw std::runtime_error("Could not convert type to string!");
    }
}

String ConvToString(std::any v) {
    std::stringstream ss;
    MultiLineManager mm(ss);

    recurseObject(v, mm);

    return ss.str();
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
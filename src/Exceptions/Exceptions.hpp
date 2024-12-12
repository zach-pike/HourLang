#pragma once

#include <iostream>
#include <exception>
#include <sstream>
#include <cstdint>

#include "Tokenizer/Tokenizer.hpp"
#include "Types.hpp"

class NoFunctionFound : public std::exception {
private:
    std::string msg;

public:
    NoFunctionFound(std::string unfoundFunction)  {
            std::stringstream ss;
            ss << "No function named \"";
            ss << unfoundFunction;
            ss << "\" Found on stack!";

            msg = ss.str();
        }

    const char* what() const noexcept override {
        return msg.c_str();
    }
};

class NoVariableFound : public std::exception {
private:
    std::string msg;

public:
    NoVariableFound(std::string unfoundVariable) {
        std::stringstream ss;
        ss << "No variable named \"";
        ss << unfoundVariable;
        ss << "\" Found on stack!";

        msg = ss.str();
    }

    const char* what() const noexcept override {
        return msg.c_str();
    }
};

class ASTBuildUnExpectedToken : public std::exception {
private:
    std::string msg;
public:
    ASTBuildUnExpectedToken(TokenType ExpectedToken, TokenType unExpectedToken, std::size_t position) {
        std::stringstream ss;
        ss << "Expected Token [";
        ss << std::string(tokenNames[(int) ExpectedToken]);
        ss << "] at position ";
        ss << position;
        ss << " but got [";
        ss << std::string(tokenNames[(int) unExpectedToken]);
        ss << "] instead";

        msg = ss.str();
    }

    const char* what() const noexcept override {
        return msg.c_str();
    }
};

class ASTBuildExpectEndOfFile : public std::exception {
private:
    std::string msg;
public:
    ASTBuildExpectEndOfFile(TokenType ExpectedToken) {
        std::stringstream ss;
        ss << "Expected token [";
        ss << std::string(tokenNames[(int) ExpectedToken]);
        ss << "] but reached end of file!";

        msg = ss.str();
    }

    const char* what() const noexcept override {
        return msg.c_str();
    }
};

class ASTBuildPeekEndOfFile : public std::exception {
public:
    const char* what() const noexcept override {
        return "Tried Peeking token, but reached end of file!";
    }
};

class InvalidParameterType : public std::exception {
private:
    std::string msg;
public:
    InvalidParameterType(VariableType expected, VariableType provided) {
        std::vector<int> types;

        // 1 here is to skip Any type
        for (int i=1; i<ARR_SZ(variableTypeOptions); i++) {
            if (expected & variableTypeOptions[i]) {
                types.push_back(i);
            }
        }

        std::stringstream ss;
        ss << "Invalid type: Expected [";

        for (int i=0; i<types.size(); i++) {
            ss << variableTypeNames[types[i]];

            if (i != (types.size() - 1)) {
                ss << " or ";
            }
        }

        ss << "] got [";
        for (int i=1; i<ARR_SZ(variableTypeOptions); i++) {
            if (provided & variableTypeOptions[i]) {
                ss << variableTypeNames[i];
                break;
            }
        }
        ss << ']';

        msg = ss.str();
    }

    const char* what() const noexcept override {
        return msg.c_str();
    }
};

class InvalidParameterCount : public std::exception {
private:
    std::string msg;
public:
    InvalidParameterCount(size_t expected) {
        std::stringstream ss;
        ss << "Invalid parameter count: Expected ";
        ss << expected;
        ss << " parameters";

        msg = ss.str();
    }

    const char* what() const noexcept override {
        return msg.c_str();
    }
};

class ModuleNotFound : public std::exception {
private:
    std::string msg;
public:
    ModuleNotFound(std::string name) {
        msg = "Could not locate module \"" + name + "\" in module paths!";
    }

    const char* what() const noexcept override {
        return msg.c_str();
    }
};
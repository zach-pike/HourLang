#pragma once

#include <iostream>
#include <exception>
#include <sstream>
#include <cstdint>

#include "Tokenizer/Tokenizer.hpp"

class NoFunctionFound : public std::exception {
private:
    std::string unfoundFunction;

public:
    NoFunctionFound(std::string _unfoundFunction):
        unfoundFunction(_unfoundFunction) {}

    const char* what() const noexcept override {
        std::stringstream ss;
        ss << "No function named \"";
        ss << unfoundFunction;
        ss << "\" Found on stack!";

        return ss.str().c_str();
    }
};

class NoVariableFound : public std::exception {
private:
    std::string unfoundVariable;

public:
    NoVariableFound(std::string _unfoundVariable):
        unfoundVariable(_unfoundVariable) {}

    const char* what() const noexcept override {
        std::stringstream ss;
        ss << "No variable named \"";
        ss << unfoundVariable;
        ss << "\" Found on stack!";

        return ss.str().c_str();
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
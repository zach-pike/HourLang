#pragma once

#include <vector>
#include <string>
#include <any>
#include <map>
#include <cstring>

enum class TokenType {
    LITERAL = 0,

    LEFT_PAREN = 1,
    RIGHT_PAREN = 2,

    LEFT_BRACKET = 3,
    RIGHT_BRACKET = 4,

    LEFT_CURLY = 5,
    RIGHT_CURLY = 6,

    COMMA = 7,
    SEMICOLON = 8,
    COLON = 9,
    SQUOTE = 10,
    DQUOTE = 11,
    PERIOD = 12,
    ASSIGN = 13,

    CMP_EQ = 14,
    CMP_NEQ = 15,
    CMP_LT = 16,
    CMP_GT = 17,
    CMP_LTE = 18,
    CMP_GTE = 19,

    FOR = 20,
    WHILE = 21,
    IF = 22,
    ELSE = 23,
    FUNCTION = 24,
    RETURN = 25,

    ADD = 26,
    SUBTRACT = 27,
    MULTIPLY = 28,
    DIVIDE = 29,

    ASSIGN_ADD = 30,
    ASSIGN_SUBTRACT = 31,
    ASSIGN_MULTIPLY = 32,
    ASSIGN_DIVIDE = 33,

    IMPORT = 34,

    BOOLEAN_NOT = 35,

    BOOLEAN_AND = 36,
    BOOLEAN_OR = 37
};

constexpr const char* tokenNames[] = {
    "LITERAL",

    "LEFT_PAREN",
    "RIGHT_PAREN",

    "LEFT_BRACKET",
    "RIGHT_BRACKET",

    "LEFT_CURLY",
    "RIGHT_CURLY",

    "COMMA",
    "SEMICOLON",
    "COLON",
    "SQUOTE",
    "DQUOTE",
    "PERIOD",
    "ASSIGN",

    "CMP_EQ",
    "CMP_NEQ",
    "CMP_LT",
    "CMP_GT",
    "CMP_LTE",
    "CMP_GTE",

    "FOR",
    "WHILE",
    "IF",
    "ELSE",
    "FUNCTION",
    "RETURN",

    "ADD",
    "SUBTRACT",
    "MULTIPLY",
    "DIVIDE",

    "ASSIGN_ADD",
    "ASSIGN_SUBTRACT",
    "ASSIGN_MULTIPLY",
    "ASSIGN_DIVIDE",

    "IMPORT",

    "BOOLEAN_NOT",
    "BOOLEAN_AND",
    "BOOLEAN_OR"
};

struct CompareByLength {
    bool operator()(const char* lhs, const char* rhs) const {
        size_t len_lhs = std::strlen(lhs);
        size_t len_rhs = std::strlen(rhs);

        // Sort by length first, then lexicographically for ties
        return (len_lhs == len_rhs) ? std::strcmp(lhs, rhs) < 0 : len_lhs > len_rhs;
    }
};

using TokenMap = std::multimap<const char*, TokenType, CompareByLength>;

TokenMap GetTokenMap();

struct Token {
    TokenType type;
    std::any   associatedData;

    Token(TokenType);
    Token(TokenType, std::any);
};

using TokenList = std::vector<Token>;

TokenList Tokenizer(std::string code);

bool IsExpressionToken(Token t);
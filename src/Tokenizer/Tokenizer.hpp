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
    SQUOTE = 9,
    DQUOTE = 10,
    ASSIGN = 11,

    CMP_EQ = 12,
    CMP_NEQ = 13,
    CMP_LT = 14,
    CMP_GT = 15,
    CMP_LTE = 16,
    CMP_GTE = 17,

    FOR = 18,
    WHILE = 19,
    IF = 20,
    FUNCTION = 21,
    RETURN = 22,

    ADD = 23,
    SUBTRACT = 24,
    MULTIPLY = 25,
    DIVIDE = 26,

    ASSIGN_ADD = 27,
    ASSIGN_SUBTRACT = 28,
    ASSIGN_MULTIPLY = 29,
    ASSIGN_DIVIDE = 30
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
    "SQUOTE",
    "DQUOTE",
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
    "FUNCTION",
    "RETURN",

    "ADD",
    "SUBTRACT",
    "MULTIPLY",
    "DIVIDE",

    "ASSIGN_ADD",
    "ASSIGN_SUBTRACT",
    "ASSIGN_MULTIPLY",
    "ASSIGN_DIVIDE"
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

bool isExpressionToken(Token t);
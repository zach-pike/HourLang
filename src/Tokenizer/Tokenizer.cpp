#include "Tokenizer.hpp"

#include <algorithm>
#include <iostream>

TokenMap GetTokenMap() {
    TokenMap tokens = {
        { "(", TokenType::LEFT_PAREN },
        { ")", TokenType::RIGHT_PAREN },
        { "[", TokenType::LEFT_BRACKET },
        { "]", TokenType::RIGHT_BRACKET },
        { "{", TokenType::LEFT_CURLY },
        { "}", TokenType::RIGHT_CURLY },

        { ",", TokenType::COMMA },
        { ";", TokenType::SEMICOLON },
        { "'", TokenType::SQUOTE },
        { "\"", TokenType::DQUOTE },
        { "=", TokenType::ASSIGN },

        { "==", TokenType::CMP_EQ },
        { "!=", TokenType::CMP_NEQ },
        { "<", TokenType::CMP_LT },
        { ">", TokenType::CMP_GT },
        { "<=", TokenType::CMP_LTE },
        { ">=", TokenType::CMP_GTE },

        { "for", TokenType::FOR },
        { "while", TokenType::WHILE },
        { "if", TokenType::IF },
        { "else", TokenType::ELSE },
        { "function", TokenType::FUNCTION },
        { "return ", TokenType::RETURN },

        { "+", TokenType::ADD },
        { "-", TokenType::SUBTRACT },
        { "*", TokenType::MULTIPLY },
        { "/", TokenType::DIVIDE },

        { "+=", TokenType::ASSIGN_ADD },
        { "-=", TokenType::ASSIGN_SUBTRACT },
        { "*=", TokenType::ASSIGN_MULTIPLY },
        { "/=", TokenType::ASSIGN_DIVIDE },

        { "return", TokenType::RETURN },
        { "!", TokenType::NOT },
    };

    return tokens;
}

static std::vector<char> GetEqualsSkipCharacters() {
    std::vector<char> a;

    for (auto t : GetTokenMap()) {
        if (std::strlen(t.first) == 2 && t.first[1] == '=') {
            a.push_back(t.first[0]);
        }
    }

    return a;
}

bool IsExpressionToken(Token t) {
    return t.type == TokenType::ADD ||
           t.type == TokenType::SUBTRACT ||
           t.type == TokenType::MULTIPLY ||
           t.type == TokenType::DIVIDE ||
           t.type == TokenType::CMP_EQ ||
           t.type == TokenType::CMP_NEQ ||
           t.type == TokenType::CMP_LT ||
           t.type == TokenType::CMP_GT ||
           t.type == TokenType::CMP_LTE ||
           t.type == TokenType::CMP_GTE;
}

Token::Token(TokenType t):
    type(t) {}

Token::Token(TokenType t, std::any d):
    type(t),
    associatedData(d) {}

TokenList Tokenizer(std::string code) {
    const TokenMap tokenMap = GetTokenMap();
    const auto     skipTokens = GetEqualsSkipCharacters();
    TokenList tokenList;
    std::string accumulator = "";
    bool stringMode = false;

    auto processAccumulator = [&](bool skip) {
        if (stringMode) {
            if (accumulator.find('"') != (accumulator.size() - 1)) return;

            tokenList.push_back(Token(TokenType::LITERAL, accumulator.substr(0, accumulator.size() - 1)));
            tokenList.push_back(Token(TokenType::DQUOTE));
            stringMode = false;

            accumulator.clear();
        } else if (!skip) {
            for (auto pair : tokenMap) {
                // Found token
                std::size_t tokenPos = accumulator.rfind(pair.first);
                if (tokenPos == std::string::npos) continue;

                if (tokenPos != 0) {
                    // Literal before this token
                    // extract it
                    tokenList.push_back(Token(TokenType::LITERAL, accumulator.substr(0, tokenPos)));
                }

                // Add rest of this token
                tokenList.push_back(Token(pair.second));
                if (pair.second == TokenType::DQUOTE) stringMode = true;

                accumulator.clear();
            }
        }
    };

    for(std::size_t i=0; i<code.size(); i++) {
        if (isspace(code[i]) && !stringMode) continue;

        accumulator += code[i];

        bool thisCharIsSkipChar = std::find(skipTokens.begin(), skipTokens.end(), code[i]) != skipTokens.end();
        bool nextCharIsEquals = i+1 < code.size() ? code[i+1] == '=' : false;

        processAccumulator(thisCharIsSkipChar &&  nextCharIsEquals);
    }

    processAccumulator(false);

    return tokenList;
}
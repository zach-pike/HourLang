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
        { ":", TokenType::COLON },
        { ".", TokenType::PERIOD },
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
        { "import", TokenType::IMPORT },
        { "not", TokenType::BOOLEAN_NOT },
        { "&&", TokenType::BOOLEAN_AND },
        { "||", TokenType::BOOLEAN_OR },
    };

    return tokens;
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
           t.type == TokenType::CMP_GTE ||
           t.type == TokenType::BOOLEAN_AND ||
           t.type == TokenType::BOOLEAN_OR;
}

static bool ContainsOnlyNumbers(std::string s) {
    for (int i=0; i<s.size(); i++) {
        if (s[i] < '0' || s[i] > '9') return false;
    }

    return true && (s.size() > 0);
}

Token::Token(TokenType t):
    type(t) {}

Token::Token(TokenType t, std::any d):
    type(t),
    associatedData(d) {}

TokenList Tokenizer(std::string code) {
    const TokenMap tokenMap = GetTokenMap();
    TokenList tokenList;
    std::string accumulator = "";

    bool stringMode = false;
    std::size_t stringCount = -1;
    char stringTerm;

    bool commentMode = false;

    auto processAccumulator = [&](bool skip) {
        if (skip) {
            return;
        };

        for (auto pair : tokenMap) {
            // Found token
            std::size_t tokenPos = accumulator.rfind(pair.first);
            if (tokenPos == std::string::npos) continue;

            if (tokenPos != 0 && pair.second == TokenType::PERIOD) {
                // Check if numbers come before this period
                std::string str = accumulator.substr(0, tokenPos);
                if (ContainsOnlyNumbers(str)) continue;
            }

            if (tokenPos != 0) {
                // Literal before this token
                // extract it
                tokenList.push_back(Token(TokenType::LITERAL, accumulator.substr(0, tokenPos)));
            }

            // Add rest of this token
            tokenList.push_back(Token(pair.second));
            accumulator.clear();

            if (
                (pair.second == TokenType::SQUOTE ||
                pair.second == TokenType::DQUOTE) &&
                !stringMode &&
                stringTerm == 0
            ) {
                stringMode = true;
                stringTerm = tokenList.back().type == TokenType::DQUOTE ? '"' : '\'';
            }

            break;
        }
    };
    
    for(std::size_t i=0; i<code.size(); i++) {

        // Are we entering comment mode?
        if (!commentMode && code[i] == '/' && (i+1) < code.size() && code[i+1] == '/') {
            commentMode = true;
        }
        
        // When we reach a newline then quit the comment mode
        if (commentMode && code[i] == '\n') {
            commentMode = false;
        }

        // If in comment mode, skip characters
        if (commentMode) continue;

        // if character is whitespace and were not in string mode, then discard the chars
        if (isspace(code[i]) && !stringMode) continue;

        accumulator += code[i];

        bool disabledStringMode = false;

        if (stringMode && code[i] == stringTerm) {
            stringMode = false;
            disabledStringMode = true;
        }

        bool shouldSkip = 
            ((
                code[i] == '=' ||
                code[i] == '!' ||
                code[i] == '>' ||
                code[i] == '<' ||
                code[i] == '&' ||
                code[i] == '|' ||
                code[i] == '+' ||
                code[i] == '-' ||
                code[i] == '*' ||
                code[i] == '/'
            ) && code[i+1] == '=') ||
            (code[i] == '&' && code[i+1] == '&') ||
            (code[i] == '|' && code[i+1] == '|') ||
            (stringMode);

        processAccumulator(shouldSkip);

        if (disabledStringMode) stringTerm = 0;
    }

    processAccumulator(false);

    return tokenList;
}
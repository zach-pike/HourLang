#include "ASTBuilder.hpp"
#include "Exceptions/Exceptions.hpp"
#include "Types.hpp"
#include <assert.h>
#include <optional>

static bool StringHasOnlyNumbers(std::string s) {
    for (char c : s) {
        if (c < '0' || c > '9') return false;
    }

    return true;
}

static std::optional<std::any> StringToValue(std::string s) {
    // Check if this could be a raw string literal
    if (s.find('.') != std::string::npos) {
        return std::stof(s);
    } else if (StringHasOnlyNumbers(s)) {
        return std::stoi(s);
    } else if (s == "true") {
        return true;
    } else if (s == "false") {
        return false;
    } else {
        // Maybe variable name?
        return std::nullopt;
    }
}

static Token PeekToken(const TokenList& tokens, std::size_t& current, int lookAhead) {
    if ((current + lookAhead) >= tokens.size()) throw ASTBuildPeekEndOfFile();

    return tokens[current + lookAhead];
}

static void SkipToken(const TokenList& tokens, std::size_t& current) {
    if (current >= tokens.size()) throw ASTBuildPeekEndOfFile();
    current += 1;
}

static std::string ExpectToken(const TokenList& tokens, std::size_t& current, TokenType type) {
    // Try to consume token of desired type or error
    if (current >= tokens.size()) throw ASTBuildExpectEndOfFile(type);

    // Get token
    auto token = tokens[current];
    if (token.type != type) throw ASTBuildUnExpectedToken(type, token.type, current);

    std::string d;

    if (token.associatedData.type() == typeid(std::string)) {
        d = std::any_cast<std::string>(token.associatedData);
    }

    current += 1;

    return d;
}

// Defs
static std::shared_ptr<ASTNode> ParseExpression(const TokenList& tokens, std::size_t& current);
static std::shared_ptr<ASTNode> ParseStatement(const TokenList& tokens, std::size_t& current);

// Statement parsing functions
static std::shared_ptr<ASTNode> ParseScope(const TokenList& tokens, std::size_t& current) {
    ExpectToken(tokens, current, TokenType::LEFT_CURLY);

    // Try and read statements until we reach the closing bracket
    ASTNodeList children;
    while(PeekToken(tokens, current, 0).type != TokenType::RIGHT_CURLY) {
        children.push_back(ParseStatement(tokens, current));
    }

    ExpectToken(tokens, current, TokenType::RIGHT_CURLY);

    return std::make_shared<ASTNode>(
        ASTNodeType::SCOPE,
        children
    );
}

static std::shared_ptr<ASTNode> ParseImport(const TokenList& tokens, std::size_t& current) {
    ExpectToken(tokens, current, TokenType::IMPORT);
    std::string importVal = ExpectToken(tokens, current, TokenType::LITERAL);
    ExpectToken(tokens, current, TokenType::SEMICOLON);

    return std::make_shared<ASTNode>(
        ASTNodeType::IMPORT,
        ASTNodeList {},
        importVal
    );
}

static std::shared_ptr<ASTNode> ParseWhile(const TokenList& tokens, std::size_t& current) {
    ExpectToken(tokens, current, TokenType::WHILE);
    ExpectToken(tokens, current, TokenType::LEFT_PAREN);

    auto expr = ParseExpression(tokens, current);

    ExpectToken(tokens, current, TokenType::RIGHT_PAREN);

    auto body = ParseScope(tokens, current);

    return std::make_shared<ASTNode>(
        ASTNodeType::WHILE,
        ASTNodeList { expr, body }
    );
}

static std::shared_ptr<ASTNode> ParseIf(const TokenList& tokens, std::size_t& current) {
    ExpectToken(tokens, current, TokenType::IF);
    ExpectToken(tokens, current, TokenType::LEFT_PAREN);

    auto cond = ParseExpression(tokens, current);
    ExpectToken(tokens, current, TokenType::RIGHT_PAREN);

    ASTNodeList ifContents;

    ifContents.push_back(cond);
    ifContents.push_back(ParseScope(tokens, current));

    while(current < tokens.size() && PeekToken(tokens, current, 0).type == TokenType::ELSE) {
        ExpectToken(tokens, current, TokenType::ELSE);
        bool isElseIf = PeekToken(tokens, current, 0).type == TokenType::IF;

        if (isElseIf) {
            ExpectToken(tokens, current, TokenType::IF);
            ExpectToken(tokens, current, TokenType::LEFT_PAREN);
            auto cond = ParseExpression(tokens, current);
            ExpectToken(tokens, current, TokenType::RIGHT_PAREN);
            auto body = ParseScope(tokens, current);

            ifContents.push_back(cond);
            ifContents.push_back(body);
        } else {
            auto body = ParseScope(tokens, current);
            ifContents.push_back(body);
        }
    }

    return std::make_shared<ASTNode>(
        ASTNodeType::IF,
        ifContents
    );
}

static std::shared_ptr<ASTNode> ParseAssignAdd(const TokenList& tokens, std::size_t& current) {
    std::string varName = ExpectToken(tokens, current, TokenType::LITERAL);
    ExpectToken(tokens, current, TokenType::ASSIGN_ADD);

    auto value = ParseExpression(tokens, current);
    ExpectToken(tokens, current, TokenType::SEMICOLON);

    return std::make_shared<ASTNode>(
        ASTNodeType::ADD_ASSIGN,
        ASTNodeList{
            value
        },
        varName
    );
}

static std::shared_ptr<ASTNode> ParseAssignSub(const TokenList& tokens, std::size_t& current) {
    std::string varName = ExpectToken(tokens, current, TokenType::LITERAL);
    ExpectToken(tokens, current, TokenType::ASSIGN_SUBTRACT);

    auto value = ParseExpression(tokens, current);
    ExpectToken(tokens, current, TokenType::SEMICOLON);

    return std::make_shared<ASTNode>(
        ASTNodeType::SUB_ASSIGN,
        ASTNodeList{
            value
        },
        varName
    );
}

static std::shared_ptr<ASTNode> ParseAssignMul(const TokenList& tokens, std::size_t& current) {
    std::string varName = ExpectToken(tokens, current, TokenType::LITERAL);
    ExpectToken(tokens, current, TokenType::ASSIGN_MULTIPLY);

    auto value = ParseExpression(tokens, current);
    ExpectToken(tokens, current, TokenType::SEMICOLON);

    return std::make_shared<ASTNode>(
        ASTNodeType::MUL_ASSIGN,
        ASTNodeList{
            value
        },
        varName
    );
}

static std::shared_ptr<ASTNode> ParseAssignDiv(const TokenList& tokens, std::size_t& current) {
    std::string varName = ExpectToken(tokens, current, TokenType::LITERAL);
    ExpectToken(tokens, current, TokenType::ASSIGN_DIVIDE);

    auto value = ParseExpression(tokens, current);
    ExpectToken(tokens, current, TokenType::SEMICOLON);

    return std::make_shared<ASTNode>(
        ASTNodeType::DIV_ASSIGN,
        ASTNodeList{
            value
        },
        varName
    );
}

static std::shared_ptr<ASTNode> ParseFor(const TokenList& tokens, std::size_t& current) {
    ExpectToken(tokens, current, TokenType::FOR);
    ExpectToken(tokens, current, TokenType::LEFT_PAREN);

    auto initializer = ParseStatement(tokens, current);

    auto condition = ParseExpression(tokens, current);
    ExpectToken(tokens, current, TokenType::SEMICOLON);

    auto increment = ParseStatement(tokens, current);

    ExpectToken(tokens, current, TokenType::RIGHT_PAREN);

    auto body = ParseScope(tokens, current);

    return std::make_shared<ASTNode>(
        ASTNodeType::FOR,
        ASTNodeList{
            initializer,
            condition,
            increment,
            body
        }
    );
}

static std::shared_ptr<ASTNode> ParseFunction(const TokenList& tokens, std::size_t& current) {
    ExpectToken(tokens, current, TokenType::FUNCTION);
    std::string name = ExpectToken(tokens, current, TokenType::LITERAL);

    ExpectToken(tokens, current, TokenType::LEFT_PAREN);

    std::vector<std::string> paramNames;

    // Get all the parameter names
    while(PeekToken(tokens, current, 0).type != TokenType::RIGHT_PAREN) {
        std::string name = ExpectToken(tokens, current, TokenType::LITERAL);
        paramNames.push_back(name);

        if (PeekToken(tokens, current, 0).type == TokenType::RIGHT_PAREN) break;
        ExpectToken(tokens, current, TokenType::COMMA);
    }

    ExpectToken(tokens, current, TokenType::RIGHT_PAREN);

    // End of function definition, now time for contents
    auto fBody = ParseScope(tokens, current);

    return std::make_shared<ASTNode>(
        ASTNodeType::FUNCTION,
        ASTNodeList{
            fBody
        },
        ASTFunctionDefInfo {
            .functionName = name,
            .params = paramNames
        }
    );
}

static std::shared_ptr<ASTNode> ParseReturn(const TokenList& tokens, std::size_t& current) {
    ExpectToken(tokens, current, TokenType::RETURN);
    std::shared_ptr<ASTNode> value = ParseExpression(tokens, current);
    ExpectToken(tokens, current, TokenType::SEMICOLON);

    return std::make_shared<ASTNode>(
        ASTNodeType::RETURN,
        ASTNodeList {
            value
        }
    );
}

static std::shared_ptr<ASTNode> ParseAssignment(const TokenList& tokens, std::size_t& current) {
    std::string name = ExpectToken(tokens, current, TokenType::LITERAL);
    ExpectToken(tokens, current, TokenType::ASSIGN);

    std::shared_ptr<ASTNode> value = ParseExpression(tokens, current);

    ExpectToken(tokens, current, TokenType::SEMICOLON);

    return std::make_shared<ASTNode>(
        ASTNodeType::ASSIGN,
        ASTNodeList {
            value
        },
        name
    );
}

static std::shared_ptr<ASTNode> ParseFunctionCall(const TokenList& tokens, std::size_t& current) {
    std::string functionName = ExpectToken(tokens, current, TokenType::LITERAL);
    ExpectToken(tokens, current, TokenType::LEFT_PAREN);

    ASTNodeList params;

    // Get a expression then a comma, repeating untill RIGHT_PAREN
    while(PeekToken(tokens, current, 0).type != TokenType::RIGHT_PAREN) {
        params.push_back(ParseExpression(tokens, current));
        
        if (PeekToken(tokens, current, 0).type == TokenType::RIGHT_PAREN) break;
        ExpectToken(tokens, current, TokenType::COMMA);
    }

    ExpectToken(tokens, current, TokenType::RIGHT_PAREN);
    ExpectToken(tokens, current, TokenType::SEMICOLON);

    return std::make_shared<ASTNode>(
        ASTNodeType::CALL,
        params,
        functionName
    );
}

static std::shared_ptr<ASTNode> TryParseRight(const TokenList& tokens, std::size_t& current, std::shared_ptr<ASTNode> lhs) {
    Token nextToken = PeekToken(tokens, current, 0);

    if (!IsExpressionToken(nextToken)) {
        return lhs;
    }

    ASTNodeType nt;
    switch(nextToken.type) {
        case TokenType::ADD: nt = ASTNodeType::ADD; break;
        case TokenType::SUBTRACT: nt = ASTNodeType::SUBTRACT; break;
        case TokenType::MULTIPLY: nt = ASTNodeType::MULTIPLY; break;
        case TokenType::DIVIDE: nt = ASTNodeType::DIVIDE; break;
        case TokenType::CMP_EQ: nt = ASTNodeType::CMP_EQ; break;
        case TokenType::CMP_NEQ: nt = ASTNodeType::CMP_NEQ; break;
        case TokenType::CMP_LT: nt = ASTNodeType::CMP_LT; break;
        case TokenType::CMP_GT: nt = ASTNodeType::CMP_GT; break;
        case TokenType::CMP_LTE: nt = ASTNodeType::CMP_LTE; break;
        case TokenType::CMP_GTE: nt = ASTNodeType::CMP_GTE; break;
        default: throw std::runtime_error("Unknown expression operator");
    }

    // Skip operator token
    SkipToken(tokens, current);

    return std::make_shared<ASTNode>(
        nt,
        ASTNodeList {
            // lhs
            lhs,
            // rhs
            ParseExpression(tokens, current)
        }
    );
}

// Expression parsing functions
static std::shared_ptr<ASTNode> ParseExpressionLiteral(const TokenList& tokens, std::size_t& current) {
    String litString = ExpectToken(tokens, current, TokenType::LITERAL);

    std::optional<Any> litVal = StringToValue(litString);

    if (litVal.has_value()) {
        return TryParseRight(
            tokens, 
            current,
            std::make_shared<ASTNode>(
                ASTNodeType::LITERAL,
                ASTNodeList {},
                litVal.value()
            )
        );
    } else {
        return TryParseRight(
            tokens, 
            current,
            std::make_shared<ASTNode>(
                ASTNodeType::VARREF,
                ASTNodeList {},
                litString
            )
        );
    }
}

static std::shared_ptr<ASTNode> ParseExpressionString(const TokenList& tokens, std::size_t& current) {
    Token startToken = PeekToken(tokens, current, 0);

    assert(startToken.type == TokenType::SQUOTE || startToken.type == TokenType::DQUOTE);

    ExpectToken(tokens, current, startToken.type);

    std::string str = ExpectToken(tokens, current, TokenType::LITERAL);

    ExpectToken(tokens, current, startToken.type);

    return TryParseRight(
        tokens, 
        current,
        std::make_shared<ASTNode>(
            ASTNodeType::LITERAL,
            ASTNodeList {},
            str
        )
    );
}

static std::shared_ptr<ASTNode> ParseExpressionParentheses(const TokenList& tokens, std::size_t& current) {
    ExpectToken(tokens, current, TokenType::LEFT_PAREN);

    auto n = ParseExpression(tokens, current);

    ExpectToken(tokens, current, TokenType::RIGHT_PAREN);

    return TryParseRight(
        tokens,
        current,
        n
    );
}

static std::shared_ptr<ASTNode> ParseExpressionFunctionCall(const TokenList& tokens, std::size_t& current) {
    String litString = ExpectToken(tokens, current, TokenType::LITERAL);

    ASTNodeList params;

    ExpectToken(tokens, current, TokenType::LEFT_PAREN);

    while (PeekToken(tokens, current, 0).type != TokenType::LEFT_PAREN) {
        params.push_back(ParseExpression(tokens, current));

        if (PeekToken(tokens, current, 0).type != TokenType::COMMA) break;
        ExpectToken(tokens, current, TokenType::COMMA);
    }

    ExpectToken(tokens, current, TokenType::RIGHT_PAREN);

    return TryParseRight(
        tokens,
        current,
        std::make_shared<ASTNode>(
            ASTNodeType::CALL,
            params,
            litString
        )
    );
}

static std::shared_ptr<ASTNode> ParseExpressionNot(const TokenList& tokens, std::size_t& current) {
    ExpectToken(tokens, current, TokenType::NOT);

    auto a = ParseExpression(tokens, current);

    ExpectToken(tokens, current, TokenType::RIGHT_PAREN);

    return TryParseRight(
        tokens,
        current,
        std::make_shared<ASTNode>(
            ASTNodeType::NOT,
            ASTNodeList { a }
        )
    );
}

static std::shared_ptr<ASTNode> ParseExpressionArrayLiteral(const TokenList& tokens, std::size_t& current) {
    ASTNodeList nodes;

    ExpectToken(tokens, current, TokenType::LEFT_BRACKET);

    while (PeekToken(tokens, current, 0).type != TokenType::RIGHT_BRACKET) {
        nodes.push_back(ParseExpression(tokens, current));

        if (PeekToken(tokens, current, 0).type != TokenType::COMMA) break;
        ExpectToken(tokens, current, TokenType::COMMA);
    }

    ExpectToken(tokens, current, TokenType::RIGHT_BRACKET);

    return TryParseRight(
        tokens,
        current,
        std::make_shared<ASTNode>(
            ASTNodeType::ARRAY_LITERAL,
            nodes
        )
    );

}

static std::shared_ptr<ASTNode> ParseExpressionDictLiteral(const TokenList& tokens, std::size_t& current) {
    ASTDictLiteralInfo dictInfo;

    ExpectToken(tokens, current, TokenType::LEFT_CURLY);

    while (PeekToken(tokens, current, 0).type != TokenType::RIGHT_CURLY) {
        String key = ExpectToken(tokens, current, TokenType::LITERAL);

        ExpectToken(tokens, current, TokenType::ASSIGN);

        auto value = ParseExpression(tokens, current);

        dictInfo.insert({ key, value });

        if (PeekToken(tokens, current, 0).type != TokenType::COMMA) break;
        ExpectToken(tokens, current, TokenType::COMMA);
    }

    ExpectToken(tokens, current, TokenType::RIGHT_CURLY);

    return TryParseRight(
        tokens,
        current,
        std::make_shared<ASTNode>(
            ASTNodeType::DICT_LITERAL,
            ASTNodeList {},
            dictInfo
        )
    );

}

static std::shared_ptr<ASTNode> ParseExpression(const TokenList& tokens, std::size_t& current) {
    Token firstToken = PeekToken(tokens, current, 0);

    switch(firstToken.type) {
        // true / 63 / 72.5
        case TokenType::LITERAL: {
            // Peek the next token
            Token nextToken = PeekToken(tokens, current, 1);

            if (nextToken.type == TokenType::LEFT_PAREN) {
                return ParseExpressionFunctionCall(tokens, current);
            } else {
                return ParseExpressionLiteral(tokens, current);
            }
        } break;

        // "string" / 'string'
        case TokenType::SQUOTE:
        case TokenType::DQUOTE: {
            return ParseExpressionString(tokens, current);
        } break;

        // ( paren group )
        case TokenType::LEFT_PAREN: {
            return ParseExpressionParentheses(tokens, current);
        } break;

        case TokenType::NOT: {
            return ParseExpressionNot(tokens, current);
        } break;
        
        // [ "Array", 12, true, 5 + 2] 
        case TokenType::LEFT_BRACKET: {
            return ParseExpressionArrayLiteral(tokens, current);
        } break;

        // Dictionary { hello = "test", test=12 }
        case TokenType::LEFT_CURLY: {
            return ParseExpressionDictLiteral(tokens, current);
        } break;

        default: throw std::runtime_error("Unknown expression type");
    }
}

static std::shared_ptr<ASTNode> ParseStatement(const TokenList& tokens, std::size_t& current) {
    auto token = PeekToken(tokens, current, 0);

    if (token.type == TokenType::FOR) {
        return ParseFor(tokens, current);
    } else if (token.type == TokenType::WHILE) {
        return ParseWhile(tokens, current);
    } else if (token.type == TokenType::IF) {
        return ParseIf(tokens, current);
    } else if (token.type == TokenType::FUNCTION) {
        return ParseFunction(tokens, current);
    } else if (token.type == TokenType::LITERAL && current + 1 < tokens.size() && PeekToken(tokens, current, 1).type == TokenType::LEFT_PAREN) {
        return ParseFunctionCall(tokens, current);
    } else if (token.type == TokenType::RETURN) {
        return ParseReturn(tokens, current);
    } else if (token.type == TokenType::LITERAL && current + 1 < tokens.size() && PeekToken(tokens, current, 1).type == TokenType::ASSIGN) {
        return ParseAssignment(tokens, current);
    }  else if (token.type == TokenType::LITERAL && current + 1 < tokens.size() && PeekToken(tokens, current, 1).type == TokenType::ASSIGN_ADD) {
        return ParseAssignAdd(tokens, current);
    } else if (token.type == TokenType::LITERAL && current + 1 < tokens.size() && PeekToken(tokens, current, 1).type == TokenType::ASSIGN_SUBTRACT) {
        return ParseAssignSub(tokens, current);
    } else if (token.type == TokenType::LITERAL && current + 1 < tokens.size() && PeekToken(tokens, current, 1).type == TokenType::ASSIGN_MULTIPLY) {
        return ParseAssignMul(tokens, current);
    } else if (token.type == TokenType::LITERAL && current + 1 < tokens.size() && PeekToken(tokens, current, 1).type == TokenType::ASSIGN_DIVIDE) {
        return ParseAssignDiv(tokens, current);
    } else if (token.type == TokenType::IMPORT) {
        return ParseImport(tokens, current);
    } else {
        throw std::runtime_error("Unsupported expression");
    }
}

ASTNodeList BuildAST(TokenList tokens) {
    std::size_t currentToken = 0;
    
    ASTNodeList ast;
    while(currentToken < tokens.size()) {
        ast.push_back(ParseStatement(tokens, currentToken));
    }

    return ast;
}
#pragma once

#include <vector>
#include <memory>
#include <any>
#include <string>

enum class ASTNodeType {
    LITERAL = 0,

    CMP_EQ = 1,
    CMP_NEQ = 2,
    CMP_LT = 3,
    CMP_GT = 4,
    CMP_LTE = 5,
    CMP_GTE = 6,

    FOR = 7,
    WHILE = 8,
    IF = 9,
    FUNCTION = 10,

    ADD = 11,
    SUBTRACT = 12,
    MULTIPLY = 13,
    DIVIDE = 14,

    CALL = 15,

    RETURN = 16,
    SCOPE = 17,
    ASSIGN = 18,
    VARREF = 19,

    ADD_ASSIGN = 20,
    SUB_ASSIGN = 21,
    MUL_ASSIGN = 22,
    DIV_ASSIGN = 23,

    IMPORT = 24,

    NOT = 25,

    NEGATIVE = 26,

    ARRAY_LITERAL = 27,

    DICT_LITERAL = 28
};

constexpr const char* nodeNames[] = {
    "LITERAL",

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

    "ADD",
    "SUBTRACT",
    "MULTIPLY",
    "DIVIDE",

    "CALL",

    "RETURN",
    "SCOPE",
    "ASSIGN",
    "VARREF",
    "ADD_ASSIGN",
    "SUB_ASSIGN",
    "MUL_ASSIGN",
    "DIV_ASSIGN",

    "IMPORT",

    "NOT",
    "ARRAY_LITERAL",
    "DICT_LITERAL"
};

struct ASTFunctionDefInfo {
    std::string functionName;
    std::vector<std::string> params;
};

class Stack;

class ASTNode {
private:
    ASTNodeType type;
    std::vector<std::shared_ptr<ASTNode>> children;
    std::any data;
public:
    ASTNode(ASTNodeType type);
    ASTNode(ASTNodeType type, std::vector<std::shared_ptr<ASTNode>> children);
    ASTNode(ASTNodeType type, std::vector<std::shared_ptr<ASTNode>> children, std::any data);

    std::any getValue(Stack& stack);

    void printDebug(int ind = 0);
};

using ASTNodeList = std::vector<std::shared_ptr<ASTNode>>;

void ExecAST(const ASTNodeList& list, Stack& stack);
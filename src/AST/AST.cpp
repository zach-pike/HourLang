#include "AST.hpp"

#include "Stack/Stack.hpp"
#include "assert.h"
#include <iostream>

#include "Exceptions/Exceptions.hpp"

#include "Utility/Conv.hpp"

ASTNode::ASTNode(ASTNodeType _type):
    type(_type) {}

ASTNode::ASTNode(ASTNodeType _type, std::vector<std::shared_ptr<ASTNode>> _children):
    type(_type),
    children(_children) {}

ASTNode::ASTNode(ASTNodeType _type, std::vector<std::shared_ptr<ASTNode>> _children, std::any _data):
    type(_type),
    children(_children),
    data(_data) {}

std::any ASTNode::getValue(Stack& stack) {
    switch(type) {
        case ASTNodeType::LITERAL: {
            assert(
                data.type() == typeid(std::string) ||
                data.type() == typeid(int) ||
                data.type() == typeid(float) ||
                data.type() == typeid(bool)
            );

            return data;
        } break;

        case ASTNodeType::CMP_EQ: {
            assert(children.size() == 2);
            auto lhs = children[0]->getValue(stack);
            auto rhs = children[1]->getValue(stack);

            if (lhs.type() == typeid(std::string) && rhs.type() == typeid(std::string)) {
                std::string s1 = std::any_cast<std::string>(lhs);
                std::string s2 =  std::any_cast<std::string>(rhs);

                return s1 == s2;
            } else if (lhs.type() == typeid(float) && rhs.type() == typeid(float)) {
                float f1 = std::any_cast<float>(lhs);
                float f2 =  std::any_cast<float>(rhs);

                return f1 == f2;
            } else if (lhs.type() == typeid(int) && rhs.type() == typeid(int)) {
                int i1 = std::any_cast<int>(lhs);
                int i2 = std::any_cast<int>(rhs);

                return i1 == i2;
            } else {
                throw std::runtime_error("Cannot compare with presented types!");
            }
        } break;

        case ASTNodeType::CMP_NEQ: {
            assert(children.size() == 2);
            auto lhs = children[0]->getValue(stack);
            auto rhs = children[1]->getValue(stack);

            if (lhs.type() == typeid(std::string) && rhs.type() == typeid(std::string)) {
                std::string s1 = std::any_cast<std::string>(lhs);
                std::string s2 =  std::any_cast<std::string>(rhs);

                return s1 != s2;
            } else if (lhs.type() == typeid(float) && rhs.type() == typeid(float)) {
                float f1 = std::any_cast<float>(lhs);
                float f2 =  std::any_cast<float>(rhs);

                return f1 != f2;
            } else if (lhs.type() == typeid(int) && rhs.type() == typeid(int)) {
                int i1 = std::any_cast<int>(lhs);
                int i2 = std::any_cast<int>(rhs);

                return i1 != i2;
            } else {
                throw std::runtime_error("Cannot compare with presented types!");
            }
        } break;

        case ASTNodeType::CMP_LT: {
            assert(children.size() == 2);
            auto lhs = children[0]->getValue(stack);
            auto rhs = children[1]->getValue(stack);

            if (lhs.type() == typeid(std::string) && rhs.type() == typeid(std::string)) {
                std::string s1 = std::any_cast<std::string>(lhs);
                std::string s2 =  std::any_cast<std::string>(rhs);

                return s1 < s2;
            } else if (lhs.type() == typeid(float) && rhs.type() == typeid(float)) {
                float f1 = std::any_cast<float>(lhs);
                float f2 =  std::any_cast<float>(rhs);

                return f1 < f2;
            } else if (lhs.type() == typeid(int) && rhs.type() == typeid(int)) {
                int i1 = std::any_cast<int>(lhs);
                int i2 = std::any_cast<int>(rhs);

                return i1 < i2;
            } else {
                throw std::runtime_error("Cannot compare with presented types!");
            }
        } break;

        case ASTNodeType::CMP_GT: {
            assert(children.size() == 2);
            auto lhs = children[0]->getValue(stack);
            auto rhs = children[1]->getValue(stack);

            if (lhs.type() == typeid(std::string) && rhs.type() == typeid(std::string)) {
                std::string s1 = std::any_cast<std::string>(lhs);
                std::string s2 =  std::any_cast<std::string>(rhs);

                return s1 > s2;
            } else if (lhs.type() == typeid(float) && rhs.type() == typeid(float)) {
                float f1 = std::any_cast<float>(lhs);
                float f2 =  std::any_cast<float>(rhs);

                return f1 > f2;
            } else if (lhs.type() == typeid(int) && rhs.type() == typeid(int)) {
                int i1 = std::any_cast<int>(lhs);
                int i2 = std::any_cast<int>(rhs);

                return i1 > i2;
            } else {
                throw std::runtime_error("Cannot compare with presented types!");
            }
        } break;

        case ASTNodeType::CMP_LTE: {
            assert(children.size() == 2);
            auto lhs = children[0]->getValue(stack);
            auto rhs = children[1]->getValue(stack);

            if (lhs.type() == typeid(std::string) && rhs.type() == typeid(std::string)) {
                std::string s1 = std::any_cast<std::string>(lhs);
                std::string s2 =  std::any_cast<std::string>(rhs);

                return s1 <= s2;
            } else if (lhs.type() == typeid(float) && rhs.type() == typeid(float)) {
                float f1 = std::any_cast<float>(lhs);
                float f2 =  std::any_cast<float>(rhs);

                return f1 <= f2;
            } else if (lhs.type() == typeid(int) && rhs.type() == typeid(int)) {
                int i1 = std::any_cast<int>(lhs);
                int i2 = std::any_cast<int>(rhs);

                return i1 <= i2;
            } else {
                throw std::runtime_error("Cannot compare with presented types!");
            }
        } break;

        case ASTNodeType::CMP_GTE: {
            assert(children.size() == 2);
            auto lhs = children[0]->getValue(stack);
            auto rhs = children[1]->getValue(stack);

            if (lhs.type() == typeid(std::string) && rhs.type() == typeid(std::string)) {
                std::string s1 = std::any_cast<std::string>(lhs);
                std::string s2 =  std::any_cast<std::string>(rhs);

                return s1 >= s2;
            } else if (lhs.type() == typeid(float) && rhs.type() == typeid(float)) {
                float f1 = std::any_cast<float>(lhs);
                float f2 =  std::any_cast<float>(rhs);

                return f1 >= f2;
            } else if (lhs.type() == typeid(int) && rhs.type() == typeid(int)) {
                int i1 = std::any_cast<int>(lhs);
                int i2 = std::any_cast<int>(rhs);

                return i1 >= i2;
            } else {
                throw std::runtime_error("Cannot compare with presented types!");
            }
        } break;

        case ASTNodeType::FOR: {
            // For loop, pretty simple
            // children
            // 0 -> initializer
            // 1 -> comparison
            // 2 -> increment
            // 3 -> for loop contents (SCOPE)

            assert(children.size() == 4);

            auto initialize = children[0];
            auto comparison = children[1];
            auto increment = children[2];

            auto loop = children[3];
            assert(loop->type == ASTNodeType::SCOPE);

            for (initialize->getValue(stack); 
                 ConvToBool(comparison->getValue(stack)); 
                 increment->getValue(stack))
            {
                loop->getValue(stack);
            }

            return std::any();
        } break;

        case ASTNodeType::WHILE: {
            // While loop children
            // 0 -> Condition
            // 1 -> Loop body (SCOPE)

            assert(children.size() == 2);

            auto condition = children[0];
            auto loop = children[1];
            assert(loop->type == ASTNodeType::SCOPE);

            while(ConvToBool(condition->getValue(stack))) {
                loop->getValue(stack);
            }

            return std::any();
        } break;

        case ASTNodeType::IF: {
            assert(children.size() >= 2);

            bool hasElse = children.size() % 2 == 1;

            int loops = hasElse ? (children.size() - 1)/2:children.size()/2;

            bool ifBlockRan = false;
            for (int i=0; i<loops; i++) {
                auto cond = children[i*2 + 0];
                auto body = children[i*2 + 1];
                assert(body->type == ASTNodeType::SCOPE);

                if (ConvToBool(cond->getValue(stack))) {
                    body->getValue(stack);
                    ifBlockRan = true;
                    break;
                }
            }

            if (hasElse && !ifBlockRan) {
                children.back()->getValue(stack);
            }
        } break;

        case ASTNodeType::FUNCTION: {
            // Make sure child is a SCOPE
            assert(children.size() == 1);
            assert(children[0]->type == ASTNodeType::SCOPE);

            // Make sure we have the correct data
            assert(data.has_value());
            assert(data.type() == typeid(ASTFunctionDefInfo));

            ASTFunctionDefInfo fData = std::any_cast<ASTFunctionDefInfo>(data);
            std::string fName = fData.functionName;

            stack.setFunction(fName, std::make_shared<Function>(children[0], fData.params));

            return std::any();
        } break;
        
        case ASTNodeType::ADD: {
            assert(children.size() == 2);
            std::any lhs = children[0]->getValue(stack);
            std::any rhs = children[1]->getValue(stack);

            if (lhs.type() == typeid(std::string) || rhs.type() == typeid(std::string)) {
                std::string s1 = lhs.type() == typeid(std::string) ? std::any_cast<std::string>(lhs) : ConvToString(lhs);
                std::string s2 = rhs.type() == typeid(std::string) ? std::any_cast<std::string>(rhs) : ConvToString(rhs);

                return s1 + s2;
            } else if (lhs.type() == typeid(float) || rhs.type() == typeid(float)) {
                float f1 = lhs.type() == typeid(float) ? std::any_cast<float>(lhs) : ConvToFloat(lhs);
                float f2 = rhs.type() == typeid(float) ? std::any_cast<float>(rhs) : ConvToFloat(rhs);

                return f1 + f2;
            } else if (lhs.type() == typeid(int) || rhs.type() == typeid(int)) {
                int i1 = lhs.type() == typeid(int) ? std::any_cast<int>(lhs) : ConvToInt(lhs);
                int i2 = rhs.type() == typeid(int) ? std::any_cast<int>(rhs) : ConvToInt(rhs);

                return i1 + i2;
            } else {
                // Only other type combo left is bool + bool
                bool b1 = std::any_cast<bool>(lhs);
                bool b2 = std::any_cast<bool>(rhs);

                return b1 || b2;
            }
        } break;

        case ASTNodeType::SUBTRACT: {
            assert(children.size() == 2);
            std::any lhs = children[0]->getValue(stack);
            std::any rhs = children[1]->getValue(stack);

            if (lhs.type() == typeid(float) && rhs.type() == typeid(float)) {
                float f1 = std::any_cast<float>(lhs);
                float f2 =  std::any_cast<float>(rhs);

                return f1 - f2;
            } else if (lhs.type() == typeid(int) && rhs.type() == typeid(int)) {
                int i1 = std::any_cast<int>(lhs);
                int i2 = std::any_cast<int>(rhs);

                return i1 - i2;
            } else {
                throw std::runtime_error("Cannot subtract with presented types!");
            }
        } break;

        case ASTNodeType::MULTIPLY: {
            assert(children.size() == 2);
            std::any lhs = children[0]->getValue(stack);
            std::any rhs = children[1]->getValue(stack);

            if (lhs.type() == typeid(float) && rhs.type() == typeid(float)) {
                float f1 = lhs.type() == typeid(float) ? std::any_cast<float>(lhs) : ConvToFloat(lhs);
                float f2 = rhs.type() == typeid(float) ? std::any_cast<float>(rhs) : ConvToFloat(rhs);

                return f1 * f2;
            } else if (lhs.type() == typeid(int) && rhs.type() == typeid(int)) {
                int i1 = lhs.type() == typeid(int) ? std::any_cast<int>(lhs) : ConvToInt(lhs);
                int i2 = rhs.type() == typeid(int) ? std::any_cast<int>(rhs) : ConvToInt(rhs);

                return i1 * i2;
            } else {
                throw std::runtime_error("Cannot multiply with string!");
            }
        } break;

        case ASTNodeType::DIVIDE: {
            assert(children.size() == 2);
            std::any lhs = children[0]->getValue(stack);
            std::any rhs = children[1]->getValue(stack);

            if (lhs.type() == typeid(float) && rhs.type() == typeid(float)) {
                float f1 = lhs.type() == typeid(float) ? std::any_cast<float>(lhs) : ConvToFloat(lhs);
                float f2 = rhs.type() == typeid(float) ? std::any_cast<float>(rhs) : ConvToFloat(rhs);

                return f1 / f2;
            } else if (lhs.type() == typeid(int) && rhs.type() == typeid(int)) {
                int i1 = lhs.type() == typeid(int) ? std::any_cast<int>(lhs) : ConvToInt(lhs);
                int i2 = rhs.type() == typeid(int) ? std::any_cast<int>(rhs) : ConvToInt(rhs);

                return i1 / i2;
            } else {
                throw std::runtime_error("Cannot divide with string!");
            }
        } break;

        case ASTNodeType::CALL: {
            // Get value of all parameters
            std::vector<std::any> params;
            for (auto& child : children) {
                params.push_back(child->getValue(stack));
            }

            // Make sure name is a string
            assert(data.has_value());
            assert(data.type() == typeid(std::string));
            std::string fName = std::any_cast<std::string>(data);

            // Get function
            auto f = stack.getFunction(fName);
            if (!f.has_value()) throw NoFunctionFound(fName);
            
            return f.value()->callFunction(params, stack);
        } break;

        case ASTNodeType::RETURN: {
            // Add value to return stack
            assert(children.size() == 1);

            stack.setReturnValue(children[0]->getValue(stack));

            return std::any();
        } break;

        case ASTNodeType::SCOPE: {
            stack.pushScope();

            for (auto& child : children) {
                child->getValue(stack);
            }

            stack.popScope();

            return std::any();
        } break;

        case ASTNodeType::ASSIGN: {
            assert(children.size() == 1);
            std::any value = children[0]->getValue(stack);

            assert(data.type() == typeid(std::string));
            std::string name = std::any_cast<std::string>(data);

            stack.setVariable(name, value);
        } break;

        case ASTNodeType::VARREF: {
            // If we get here we resolve the variable
            std::string vName = std::any_cast<std::string>(data);
            auto var = stack.getVariable(vName);

            if (!var.has_value()) throw NoVariableFound(vName);
            return var.value();
        } break;

        case ASTNodeType::ADD_ASSIGN: {
            assert(children.size() == 1);
            
            assert(data.type() == typeid(std::string));
            auto varName = std::any_cast<std::string>(data);

            auto var = stack.getVariable(varName);
            if (!var.has_value()) throw NoVariableFound(varName);

            std::any lhs = var.value();
            std::any rhs = children[0]->getValue(stack);

            if (lhs.type() == typeid(std::string) || rhs.type() == typeid(std::string)) {
                std::string s1 = lhs.type() == typeid(std::string) ? std::any_cast<std::string>(lhs) : ConvToString(lhs);
                std::string s2 = rhs.type() == typeid(std::string) ? std::any_cast<std::string>(rhs) : ConvToString(rhs);

                stack.setVariable(varName, s1 + s2);
            } else if (lhs.type() == typeid(float) || rhs.type() == typeid(float)) {
                float f1 = lhs.type() == typeid(float) ? std::any_cast<float>(lhs) : ConvToFloat(lhs);
                float f2 = rhs.type() == typeid(float) ? std::any_cast<float>(rhs) : ConvToFloat(rhs);

                stack.setVariable(varName, f1 + f2);
            } else if (lhs.type() == typeid(int) || rhs.type() == typeid(int)) {
                int i1 = lhs.type() == typeid(int) ? std::any_cast<int>(lhs) : ConvToInt(lhs);
                int i2 = rhs.type() == typeid(int) ? std::any_cast<int>(rhs) : ConvToInt(rhs);

                stack.setVariable(varName, i1 + i2);
            } else {
                // Only other type combo left is bool + bool
                bool b1 = std::any_cast<bool>(lhs);
                bool b2 = std::any_cast<bool>(rhs);

                stack.setVariable(varName, b1 + b2);
            }

            return std::any();
        } break;

    }

    return std::any();
}

static void printInd(int k) {
    for(int i=0; i<k; i++)
        printf("  ");
}

void ASTNode::printDebug(int ind) {
    printInd(ind); std::cout << '[' << nodeNames[(int) type] << "] ";

    if (type == ASTNodeType::LITERAL) {
        std::cout << '(' << ConvToString(data) << ") {";
    } else if (type == ASTNodeType::ASSIGN || type == ASTNodeType::VARREF || type == ASTNodeType::CALL) {
        std::cout << '(' << std::any_cast<std::string>(data) << ") {";
    } else {
        std::cout << "{";
    }

    if (children.size() > 0) std::cout << '\n';

    for (auto& child : children) {
        child->printDebug(ind + 1);
    }

    if (children.size() > 0) printInd(ind);
    std::cout << "}\n";
}
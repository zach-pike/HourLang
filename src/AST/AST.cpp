#include "AST.hpp"

#include "Stack/Stack.hpp"
#include "assert.h"
#include <iostream>

#include "Exceptions/Exceptions.hpp"
#include "Utility/GetVarTypeString.hpp"

#include "Utility/Conv.hpp"
#include "Utility/Math.hpp"

#include "ASTBuilder.hpp"

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
                data.type() == typeid(String) ||
                data.type() == typeid(Int) ||
                data.type() == typeid(Float) ||
                data.type() == typeid(Bool) ||
                data.type() == typeid(Array)
            );

            return data;
        } break;

        case ASTNodeType::CMP_EQ: {
            assert(children.size() == 2);
            auto lhs = children[0]->getValue(stack);
            auto rhs = children[1]->getValue(stack);

            if (lhs.type() == typeid(String) && rhs.type() == typeid(String)) {
                String s1 = std::any_cast<String>(lhs);
                String s2 =  std::any_cast<String>(rhs);

                return s1 == s2;
            } else if (lhs.type() == typeid(Float) || rhs.type() == typeid(Float)) {
                Float f1 = ConvToFloat(lhs);
                Float f2 = ConvToFloat(rhs);

                return f1 == f2;
            } else if (lhs.type() == typeid(Int) && rhs.type() == typeid(Int)) {
                Int i1 = std::any_cast<Int>(lhs);
                Int i2 = std::any_cast<Int>(rhs);

                return i1 == i2;
            } else {
                throw std::runtime_error("Cannot compare with presented types!");
            }
        } break;

        case ASTNodeType::CMP_NEQ: {
            assert(children.size() == 2);
            auto lhs = children[0]->getValue(stack);
            auto rhs = children[1]->getValue(stack);

            if (lhs.type() == typeid(String) && rhs.type() == typeid(String)) {
                String s1 = std::any_cast<String>(lhs);
                String s2 =  std::any_cast<String>(rhs);

                return s1 != s2;
            } else if (lhs.type() == typeid(Float) || rhs.type() == typeid(Float)) {
                Float f1 = ConvToFloat(lhs);
                Float f2 = ConvToFloat(rhs);

                return f1 != f2;
            } else if (lhs.type() == typeid(Int) && rhs.type() == typeid(Int)) {
                Int i1 = std::any_cast<Int>(lhs);
                Int i2 = std::any_cast<Int>(rhs);

                return i1 != i2;
            } else {
                throw std::runtime_error("Cannot compare with presented types!");
            }
        } break;

        case ASTNodeType::CMP_LT: {
            assert(children.size() == 2);
            auto lhs = children[0]->getValue(stack);
            auto rhs = children[1]->getValue(stack);

            if (lhs.type() == typeid(String) && rhs.type() == typeid(String)) {
                String s1 = std::any_cast<String>(lhs);
                String s2 =  std::any_cast<String>(rhs);

                return s1 < s2;
            } else if (lhs.type() == typeid(Float) || rhs.type() == typeid(Float)) {
                Float f1 = ConvToFloat(lhs);
                Float f2 =  ConvToFloat(rhs);

                return f1 < f2;
            } else if (lhs.type() == typeid(Int) && rhs.type() == typeid(Int)) {
                Int i1 = std::any_cast<Int>(lhs);
                Int i2 = std::any_cast<Int>(rhs);

                return i1 < i2;
            } else {
                throw std::runtime_error("Cannot compare with presented types! lt");
            }
        } break;

        case ASTNodeType::CMP_GT: {
            assert(children.size() == 2);
            auto lhs = children[0]->getValue(stack);
            auto rhs = children[1]->getValue(stack);

            if (lhs.type() == typeid(String) && rhs.type() == typeid(String)) {
                String s1 = std::any_cast<String>(lhs);
                String s2 =  std::any_cast<String>(rhs);

                return s1 > s2;
            } else if (lhs.type() == typeid(Float) || rhs.type() == typeid(Float)) {
                Float f1 = ConvToFloat(lhs);
                Float f2 = ConvToFloat(rhs);

                return f1 > f2;
            } else if (lhs.type() == typeid(Int) && rhs.type() == typeid(Int)) {
                Int i1 = std::any_cast<Int>(lhs);
                Int i2 = std::any_cast<Int>(rhs);

                return i1 > i2;
            } else {
                throw std::runtime_error("Cannot compare with presented types! gt");
            }
        } break;

        case ASTNodeType::CMP_LTE: {
            assert(children.size() == 2);
            auto lhs = children[0]->getValue(stack);
            auto rhs = children[1]->getValue(stack);

            if (lhs.type() == typeid(String) && rhs.type() == typeid(String)) {
                String s1 = std::any_cast<String>(lhs);
                String s2 =  std::any_cast<String>(rhs);

                return s1 <= s2;
            } else if (lhs.type() == typeid(Float) || rhs.type() == typeid(Float)) {
                Float f1 = ConvToFloat(lhs);
                Float f2 = ConvToFloat(rhs);

                return f1 <= f2;
            } else if (lhs.type() == typeid(Int) && rhs.type() == typeid(Int)) {
                Int i1 = std::any_cast<Int>(lhs);
                Int i2 = std::any_cast<Int>(rhs);

                return i1 <= i2;
            } else {
                throw std::runtime_error("Cannot compare with presented types! lte " + String(GetVarTypeString(lhs)));
            }
        } break;

        case ASTNodeType::CMP_GTE: {
            assert(children.size() == 2);
            auto lhs = children[0]->getValue(stack);
            auto rhs = children[1]->getValue(stack);

            if (lhs.type() == typeid(String) && rhs.type() == typeid(String)) {
                String s1 = std::any_cast<String>(lhs);
                String s2 =  std::any_cast<String>(rhs);

                return s1 >= s2;
            } else if (lhs.type() == typeid(Float) || rhs.type() == typeid(Float)) {
                Float f1 = ConvToFloat(lhs);
                Float f2 = ConvToFloat(rhs);

                return f1 >= f2;
            } else if (lhs.type() == typeid(Int) && rhs.type() == typeid(Int)) {
                Int i1 = std::any_cast<Int>(lhs);
                Int i2 = std::any_cast<Int>(rhs);

                return i1 >= i2;
            } else {
                throw std::runtime_error("Cannot compare with presented types! gte " + String(GetVarTypeString(lhs)));
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

            stack.pushScope();

            for (initialize->getValue(stack); 
                 ConvToBool(comparison->getValue(stack)); 
                 increment->getValue(stack))
            {
                loop->getValue(stack);
            }

            stack.popScope();


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

            return Add(lhs, rhs);
        } break;

        case ASTNodeType::SUBTRACT: {
            assert(children.size() == 2);
            std::any lhs = children[0]->getValue(stack);
            std::any rhs = children[1]->getValue(stack);

            return Subtract(lhs, rhs);
        } break;

        case ASTNodeType::MULTIPLY: {
            assert(children.size() == 2);
            std::any lhs = children[0]->getValue(stack);
            std::any rhs = children[1]->getValue(stack);

            return Multiply(lhs, rhs);
        } break;

        case ASTNodeType::DIVIDE: {
            assert(children.size() == 2);
            std::any lhs = children[0]->getValue(stack);
            std::any rhs = children[1]->getValue(stack);

            return Divide(lhs, rhs);
        } break;

        case ASTNodeType::CALL: {
            // Get value of all parameters
            Array params;
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

            stack.setVariable(varName, Add(lhs, rhs));

            return std::any();
        } break;

        case ASTNodeType::SUB_ASSIGN: {
            assert(children.size() == 1);
            
            assert(data.type() == typeid(std::string));
            auto varName = std::any_cast<std::string>(data);

            auto var = stack.getVariable(varName);
            if (!var.has_value()) throw NoVariableFound(varName);

            std::any lhs = var.value();
            std::any rhs = children[0]->getValue(stack);

            stack.setVariable(varName, Subtract(lhs, rhs));

            return std::any();
        } break;

        case ASTNodeType::MUL_ASSIGN: {
            assert(children.size() == 1);
            
            assert(data.type() == typeid(std::string));
            auto varName = std::any_cast<std::string>(data);

            auto var = stack.getVariable(varName);
            if (!var.has_value()) throw NoVariableFound(varName);

            std::any lhs = var.value();
            std::any rhs = children[0]->getValue(stack);

            stack.setVariable(varName, Multiply(lhs, rhs));

            return std::any();
        } break;

        case ASTNodeType::DIV_ASSIGN: {
            assert(children.size() == 1);
            
            assert(data.type() == typeid(std::string));
            auto varName = std::any_cast<std::string>(data);

            auto var = stack.getVariable(varName);
            if (!var.has_value()) throw NoVariableFound(varName);

            std::any lhs = var.value();
            std::any rhs = children[0]->getValue(stack);

            stack.setVariable(varName, Divide(lhs, rhs));

            return std::any();
        } break;

        case ASTNodeType::IMPORT: {
            assert(data.type() == typeid(std::string));
            std::string fName = std::any_cast<std::string>(data);

            stack.import(fName);

            return std::any();
        }

        case ASTNodeType::BOOLEAN_NOT: {
            assert(children.size() == 1);
            return !ConvToBool(children[0]->getValue(stack));
        } break;

        case ASTNodeType::NEGATIVE: {
            assert(children.size() == 1);
            auto val = children[0]->getValue(stack);

            if (val.type() == typeid(Float)) {
                Float f = std::any_cast<Float>(val);

                return -f;
            } else if (val.type() == typeid(Int)) {
                Int i = std::any_cast<Int>(val);

                return -i;
            }

            throw std::runtime_error("Cannot negate " + std::string(GetVarTypeString(val)));
        } break;

        case ASTNodeType::ARRAY_LITERAL: {
            Array a;

            for (auto& c : children) {
                a.push_back(c->getValue(stack));
            }

            return a;
        } break;

        case ASTNodeType::DICT_LITERAL: {
            auto a = std::any_cast<ASTDictLiteralInfo>(data);

            Dict d;

            for (auto& c : a) {
                d.insert({ c.first, c.second->getValue(stack) });
            }

            return d;
        } break;

        case ASTNodeType::BOOLEAN_AND: {
            assert(children.size() == 2);

            return ConvToBool(children[0]->getValue(stack)) && ConvToBool(children[1]->getValue(stack));
        } break;

        case ASTNodeType::BOOLEAN_OR: {
            assert(children.size() == 2);

            return ConvToBool(children[0]->getValue(stack)) || ConvToBool(children[1]->getValue(stack));
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

    if (data.has_value()) {
        std::cout
            << "Data{ "
            << GetVarTypeString(data)
            << '('
            << ConvToString(data)
            << ") } {";
    }

    if (children.size() > 0) std::cout << '\n';

    for (auto& child : children) {
        child->printDebug(ind + 1);
    }

    if (children.size() > 0) printInd(ind);
    std::cout << "}\n";
}

void ExecAST(const ASTNodeList& list, Stack& stack) {
    try {
        for (const auto& n : list) {
            n->getValue(stack);
            // n->printDebug();
        }
    } catch (std::exception& e) {
        std::cout << "Exception thrown in execution!\n"
                  << e.what() << '\n';
    }
}
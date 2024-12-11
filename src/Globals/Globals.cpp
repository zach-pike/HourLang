#include "Globals.hpp"

#include <any>
#include <vector>
#include <iostream>
#include <cmath>

#include "Utility/Conv.hpp"
#include "Utility/GetVarTypeString.hpp"
#include "Stack/Stack.hpp"

#include "AST/AST.hpp"
#include "AST/ASTBuilder.hpp"
#include "Tokenizer/Tokenizer.hpp"

static std::any printlnFunc(std::vector<std::any> params, std::vector<std::string> paramNames, Stack& s) {
    for (int i=0; i<params.size(); i++) {
        std::cout << ConvToString(params[i]);
        if (i != (params.size() - 1)) std::cout << ' ';
    }
    std::cout << '\n';
    return std::any();
}

static std::any printFunc(std::vector<std::any> params, std::vector<std::string> paramNames, Stack& s) {
    for (int i=0; i<params.size(); i++) {
        std::cout << ConvToString(params[i]);
        if (i != (params.size() - 1)) std::cout << ' ';
    }
    return std::any();
}

static std::any typeFunc(std::vector<std::any> params, std::vector<std::string> paramNames, Stack& s) {
    return std::string(GetVarTypeString(params[0]));
}

static std::any minFunc(std::vector<std::any> params, std::vector<std::string> paramNames, Stack& s) {
    if (params[0].type() == typeid(float) || params[1].type() == typeid(float)) {
        float f1 = params[0].type() == typeid(float) ? std::any_cast<float>(params[0]) : ConvToFloat(params[0]);
        float f2 = params[1].type() == typeid(float) ? std::any_cast<float>(params[1]) : ConvToFloat(params[1]);

        return std::min(f1, f2);
    } else if (params[0].type() == typeid(int) && params[1].type() == typeid(int)) {
        int i1 = std::any_cast<int>(params[0]);
        int i2 =  std::any_cast<int>(params[1]);

        return std::min(i1, i2);
    } else {
        throw std::runtime_error("Cannot find min with types " + std::string(GetVarTypeString(params[0])) + " and " + std::string(GetVarTypeString(params[1])));
    }
}

static std::any maxFunc(std::vector<std::any> params, std::vector<std::string> paramNames, Stack& s) {
    if (params[0].type() == typeid(float) || params[1].type() == typeid(float)) {
        float f1 = params[0].type() == typeid(float) ? std::any_cast<float>(params[0]) : ConvToFloat(params[0]);
        float f2 = params[1].type() == typeid(float) ? std::any_cast<float>(params[1]) : ConvToFloat(params[1]);

        return std::max(f1, f2);
    } else if (params[0].type() == typeid(int) && params[1].type() == typeid(int)) {
        int i1 = std::any_cast<int>(params[0]);
        int i2 =  std::any_cast<int>(params[1]);
 
        return std::max(i1, i2); 
    } else {
        throw std::runtime_error("Cannot find max with types " + std::string(GetVarTypeString(params[0])) + " and " + std::string(GetVarTypeString(params[1])));
    }
}

static std::any randIntFunc(std::vector<std::any> params, std::vector<std::string> paramNames, Stack& s) {
    int min = ConvToInt(params[0]);
    int max = ConvToInt(params[1]);

    return (int)(min + rand() % (max - min + 1));
}

static std::any randomFunc(std::vector<std::any> params, std::vector<std::string> paramNames, Stack& s) {
    return (float)rand() / (float)INT_MAX;
}

static std::any toStringFunc(std::vector<std::any> params, std::vector<std::string> paramNames, Stack& s) {
    return ConvToString(params[0]);
}

static std::any toIntFunc(std::vector<std::any> params, std::vector<std::string> paramNames, Stack& s) {
    return ConvToInt(params[0]);
}

static std::any toBoolFunc(std::vector<std::any> params, std::vector<std::string> paramNames, Stack& s) {
    return ConvToBool(params[0]);
}

static std::any toFloatFunc(std::vector<std::any> params, std::vector<std::string> paramNames, Stack& s) {
    return ConvToFloat(params[0]);
}

static std::any toArrayFunc(std::vector<std::any> params, std::vector<std::string> paramNames, Stack& s) {
    return params;
}

static std::any inputFunc(std::vector<std::any> params, std::vector<std::string> paramNames, Stack& s) {
    std::string s;
    std::getline(std::cin, s);
    return s;
}

static std::any sizeFunc(std::vector<std::any> params, std::vector<std::string> paramNames, Stack& s) {
    if (params[0].type() == typeid(std::string))
        return (int)(std::any_cast<std::string>(params[0]).size());
    else if (params[0].type() == typeid(std::vector<std::any>)) {
        return (int)(std::any_cast<std::vector<std::any>>(params[0]).size());
    }

    throw std::runtime_error("Cannot determine Size of " + std::string(GetVarTypeString(params[0])));
    return std::any();
}

static int safe_mod(int a, int b) {
    return ((a % b) + b) % b;
}

static std::any modFunc(std::vector<std::any> params, std::vector<std::string> paramNames, Stack& s) {
    if (params[0].type() == typeid(float) || params[1].type() == typeid(float)) {
        float f1 = params[0].type() == typeid(float) ? std::any_cast<float>(params[0]) : ConvToFloat(params[0]);
        float f2 = params[1].type() == typeid(float) ? std::any_cast<float>(params[1]) : ConvToFloat(params[1]);

        return std::fmod(f1, f2);
    } else if (params[0].type() == typeid(int) && params[1].type() == typeid(int)) {
        int i1 = std::any_cast<int>(params[0]);
        int i2 =  std::any_cast<int>(params[1]);

        return safe_mod(i1, i2);
    } else {
        throw std::runtime_error("Cannot find mod with types " + std::string(GetVarTypeString(params[0])) + " and " + std::string(GetVarTypeString(params[1])));
    }
}

static std::any appendFunc(std::vector<std::any> params, std::vector<std::string> paramNames, Stack& s) {
    if (params[0].type() == typeid(std::string)) {
        auto a = std::any_cast<std::string>(params[0]);

        std::string d = ConvToString(params[1]);
        a.insert(a.end(), d.begin(), d.end());

        return a;
    } else if (params[0].type() == typeid(std::vector<std::any>)) {
        auto a = std::any_cast<std::vector<std::any>>(params[0]);
        
        if (params[1].type() == typeid(std::vector<std::any>)) {
            auto b = std::any_cast<std::vector<std::any>>(params[1]);
            a.insert(a.end(), b.begin(), b.end());
        } else {
            a.push_back(params[1]);
        }

        return a;
    } else {
        throw std::runtime_error("Can't append to [" + std::string(GetVarTypeString(params[0])) + "]");
    }

    return std::any();
} 

static std::any getFunc(std::vector<std::any> params, std::vector<std::string> paramNames, Stack& s) {
    if (params[0].type() == typeid(std::string)) {
        auto a = std::any_cast<std::string>(params[0]);
        int b = ConvToInt(params[1]);

        return a.substr(b, 1);
    } else if (params[0].type() == typeid(std::vector<std::any>)) {
        auto a = std::any_cast<std::vector<std::any>>(params[0]);
        int b = ConvToInt(params[1]);

        return a.at(b);
    } else {
        throw std::runtime_error("Can't get [" + std::string(GetVarTypeString(params[0])) + "]");
    }

    return std::any();
} 

static std::any setFunc(std::vector<std::any> params, std::vector<std::string> paramNames, Stack& s) {
    if (params[0].type() == typeid(std::string)) {
        auto a = std::any_cast<std::string>(params[0]);
        int b = ConvToInt(params[1]);

        std::string c = ConvToString(params[2]);

        a.at(b) = c.at(0);
        return a;
    } else if (params[0].type() == typeid(std::vector<std::any>)) {
        auto a = std::any_cast<std::vector<std::any>>(params[0]);
        int b = ConvToInt(params[1]);

        a.at(b) = params[2];
        return a;
    } else {
        throw std::runtime_error("Can't set [" + std::string(GetVarTypeString(params[0])) + "]");
    }

    return std::any();
} 

static std::any popFunc(std::vector<std::any> params, std::vector<std::string> paramNames, Stack& s) {
    if (params[0].type() == typeid(std::string)) {
        auto a = std::any_cast<std::string>(params[0]);
        a.erase(a.size() - 1);
        return a;
    } else if (params[0].type() == typeid(std::vector<std::any>)) {
        auto a = std::any_cast<std::vector<std::any>>(params[0]);
        a.pop_back();
        return a;
    } else {
        throw std::runtime_error("Can't pop [" + std::string(GetVarTypeString(params[0])) + "]");
    }
}

static std::any eraseFunc(std::vector<std::any> params, std::vector<std::string> paramNames, Stack& s) {
    if (params[0].type() == typeid(std::string)) {
        auto a = std::any_cast<std::string>(params[0]);

        int start = ConvToInt(params[1]);
        int n = ConvToInt(params[2]);

        a.erase(start, n);

        return a;
    } else if (params[0].type() == typeid(std::vector<std::any>)) {
        auto a = std::any_cast<std::vector<std::any>>(params[0]);
        int start = ConvToInt(params[1]);
        int n = ConvToInt(params[2]);

        a.erase(a.begin() + start, a.begin() + start + n);
        return a;
    } else {
        throw std::runtime_error("Can't pop [" + std::string(GetVarTypeString(params[0])) + "]");
    }
}

static std::any evalFunc(std::vector<std::any> params, std::vector<std::string> paramNames, Stack& s) {
    TokenList tokens = Tokenizer(ConvToString(params[0]));
    ASTNodeList n = BuildAST(tokens);
    ExecAST(n, s);

    return std::any();
}

void InitGlobals(Stack& s) {
    std::vector<std::string> oneParam = { "a" };
    std::vector<std::string> twoParam = { "a", "b" };
    std::vector<std::string> threeParam = { "a", "b" };
    
    s.setFunction("print", std::make_shared<Function>(printFunc, oneParam));
    s.setFunction("println", std::make_shared<Function>(printlnFunc, oneParam));
    s.setFunction("input", std::make_shared<Function>(inputFunc, std::vector<std::string>()));

    s.setFunction("int", std::make_shared<Function>(toIntFunc, oneParam));
    s.setFunction("float", std::make_shared<Function>(toFloatFunc, oneParam));
    s.setFunction("bool", std::make_shared<Function>(toBoolFunc, oneParam));
    s.setFunction("string", std::make_shared<Function>(toStringFunc, oneParam));
    s.setFunction("array", std::make_shared<Function>(toArrayFunc, oneParam));
    
    
    s.setFunction("min", std::make_shared<Function>(minFunc, twoParam));
    s.setFunction("max", std::make_shared<Function>(maxFunc, twoParam));
    s.setFunction("mod", std::make_shared<Function>(modFunc, oneParam));
    s.setFunction("randomInt", std::make_shared<Function>(randIntFunc, twoParam));
    s.setFunction("random", std::make_shared<Function>(randomFunc, std::vector<std::string>()));

    s.setFunction("append", std::make_shared<Function>(appendFunc, twoParam));
    s.setFunction("get", std::make_shared<Function>(getFunc, twoParam));
    s.setFunction("set", std::make_shared<Function>(setFunc, threeParam));
    s.setFunction("size", std::make_shared<Function>(sizeFunc, oneParam));
    s.setFunction("type", std::make_shared<Function>(typeFunc, oneParam));

    s.setFunction("pop", std::make_shared<Function>(popFunc, oneParam));
    s.setFunction("erase", std::make_shared<Function>(eraseFunc, threeParam));
}

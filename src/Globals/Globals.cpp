#include "Globals.hpp"

#include <any>
#include <vector>
#include <iostream>
#include <cmath>
#include <sstream>

#include "Utility/Conv.hpp"
#include "Utility/GetVarTypeString.hpp"
#include "Stack/Stack.hpp"

#include "AST/AST.hpp"
#include "AST/ASTBuilder.hpp"
#include "Tokenizer/Tokenizer.hpp"

static std::any minFunc(Array params, Stack& s) {
    if (params[0].type() == typeid(float) || params[1].type() == typeid(float)) {
        float f1 = params[0].type() == typeid(float) ? std::any_cast<float>(params[0]) : ConvToFloat(params[0]);
        float f2 = params[1].type() == typeid(float) ? std::any_cast<float>(params[1]) : ConvToFloat(params[1]);

        return std::min(f1, f2);
    } else {
        int i1 = std::any_cast<int>(params[0]);
        int i2 =  std::any_cast<int>(params[1]);

        return std::min(i1, i2);
    }
}

static std::any maxFunc(Array params, Stack& s) {
    if (params[0].type() == typeid(float) || params[1].type() == typeid(float)) {
        float f1 = params[0].type() == typeid(float) ? std::any_cast<float>(params[0]) : ConvToFloat(params[0]);
        float f2 = params[1].type() == typeid(float) ? std::any_cast<float>(params[1]) : ConvToFloat(params[1]);

        return std::max(f1, f2);
    } else  {
        int i1 = std::any_cast<int>(params[0]);
        int i2 =  std::any_cast<int>(params[1]);
 
        return std::max(i1, i2); 
    }
}

static std::any randIntFunc(Array params, Stack& s) {
    Int min = std::any_cast<Int>(params[0]);
    Int max = std::any_cast<Int>(params[1]);

    return (int)(min + rand() % (max - min + 1));
}

static std::any randomFunc(Array params, Stack& s) {
    return (float)rand() / (float)INT_MAX;
}

static std::any toStringFunc(Array params, Stack& s) {
    return ConvToString(params[0]);
}

static std::any toIntFunc(Array params, Stack& s) {
    return ConvToInt(params[0]);
}

static std::any toBoolFunc(Array params, Stack& s) {
    return ConvToBool(params[0]);
}

static std::any toFloatFunc(Array params, Stack& s) {
    return ConvToFloat(params[0]);
}

static std::any toArrayFunc(Array params, Stack& s) {
    return std::any_cast<Array>(params.back());
}

static std::any inputFunc(Array params, Stack& s) {
    std::string k;
    std::getline(std::cin, k);
    return k;
}

static std::any sizeFunc(Array params, Stack& s) {
    if (params[0].type() == typeid(String))
        return (int)(std::any_cast<String>(params[0]).size());
    else if (params[0].type() == typeid(Array)) {
        return (int)(std::any_cast<Array>(params[0]).size());
    }

    throw std::runtime_error("Cannot determine Size of " + std::string(GetVarTypeString(params[0])));
    return std::any();
}

static int safe_mod(int a, int b) {
    return ((a % b) + b) % b;
}

static std::any modFunc(Array params, Stack& s) {
    if (params[0].type() == typeid(float) || params[1].type() == typeid(float)) {
        float f1 = params[0].type() == typeid(float) ? std::any_cast<float>(params[0]) : ConvToFloat(params[0]);
        float f2 = params[1].type() == typeid(float) ? std::any_cast<float>(params[1]) : ConvToFloat(params[1]);

        return std::fmod(f1, f2);
    } else {
        int i1 = std::any_cast<int>(params[0]);
        int i2 =  std::any_cast<int>(params[1]);

        return safe_mod(i1, i2);
    }
}

static std::any appendFunc(Array params, Stack& s) {
    if (params[0].type() == typeid(String)) {
        auto a = std::any_cast<String>(params[0]);

        String d = std::any_cast<String>(params[1]);
        a.insert(a.end(), d.begin(), d.end());

        return a;
    } else if (params[0].type() == typeid(Array)) {
        auto a = std::any_cast<Array>(params[0]);
        
        // If 2nd item is a array, then append items of that array to the obj
        if (params[1].type() == typeid(Array)) {
            auto b = std::any_cast<Array>(params[1]);
            a.insert(a.end(), b.begin(), b.end());
        } else {
            a.push_back(params[1]);
        }

        return a;
    }

    return std::any();
} 

static std::any getFunc(Array params, Stack& s) {
    if (params[0].type() == typeid(std::string)) {
        auto a = std::any_cast<std::string>(params[0]);
        Int b = std::any_cast<Int>(params[1]);

        return a.substr(b, 1);
    } else if (params[0].type() == typeid(Array)) {
        auto a = std::any_cast<Array>(params[0]);
        Int b = std::any_cast<Int>(params[1]);

        return a.at(b);
    }

    return std::any();
} 

static std::any setFunc(Array params, Stack& s) {
    if (params[0].type() == typeid(String)) {
        auto a = std::any_cast<String>(params[0]);
        Int b = std::any_cast<Int>(params[1]);

        String c = ConvToString(params[2]);

        a.at(b) = c.at(0);
        return a;
    } else if (params[0].type() == typeid(Array)) {
        auto a = std::any_cast<Array>(params[0]);
        int b = ConvToInt(params[1]);

        a.at(b) = params[2];
        return a;
    } else {
        throw std::runtime_error("Can't set [" + std::string(GetVarTypeString(params[0])) + "]");
    }

    return std::any();
} 

static std::any popFunc(Array params, Stack& s) {
    if (params[0].type() == typeid(std::string)) {
        auto a = std::any_cast<std::string>(params[0]);
        a.erase(a.size() - 1);
        return a;
    } else if (params[0].type() == typeid(Array)) {
        auto a = std::any_cast<Array>(params[0]);
        a.pop_back();
        return a;
    } else {
        throw std::runtime_error("Can't pop [" + std::string(GetVarTypeString(params[0])) + "]");
    }
}

static std::any eraseFunc(Array params, Stack& s) {
    if (params[0].type() == typeid(std::string)) {
        auto a = std::any_cast<std::string>(params[0]);

        int start = ConvToInt(params[1]);
        int n = ConvToInt(params[2]);

        a.erase(start, n);

        return a;
    } else if (params[0].type() == typeid(Array)) {
        auto a = std::any_cast<Array>(params[0]);
        int start = ConvToInt(params[1]);
        int n = ConvToInt(params[2]);

        a.erase(a.begin() + start, a.begin() + start + n);
        return a;
    } else {
        throw std::runtime_error("Can't pop [" + std::string(GetVarTypeString(params[0])) + "]");
    }
}

static std::any evalFunc(Array params, Stack& s) {
    TokenList tokens = Tokenizer(ConvToString(params[0]));
    ASTNodeList n = BuildAST(tokens);
    ExecAST(n, s);

    return std::any();
}

static std::any asciiFunc(Array params, Stack& s) {
    int i = std::any_cast<int>(params[0]);

    String l;
    l.push_back((char) i);
    return l;
}


void InitGlobals(Stack& s, PrintFunction& pf, NewlineFunction& nf) {
    auto noArgs = ExternalParameterInformation{
        .requiredVariableTypes = std::vector<VariableType>(),
        .hasVaArgs = false,
        .minVaArgs = 0,
        .maxVaArgs = 0,
        .vaType = VariableType::ANY
    };

    auto oneRequiredAny = ExternalParameterInformation{
        .requiredVariableTypes = std::vector<VariableType>({ VariableType::ANY }),
        .hasVaArgs = false,
        .minVaArgs = 0,
        .maxVaArgs = 0,
        .vaType = VariableType::ANY
    };

    auto twoRequiredAny = ExternalParameterInformation{
        .requiredVariableTypes = std::vector<VariableType>({ VariableType::ANY, VariableType::ANY }),
        .hasVaArgs = false,
        .minVaArgs = 0,
        .maxVaArgs = 0,
        .vaType = VariableType::ANY
    };

    auto twoRequiredNum = ExternalParameterInformation{
        .requiredVariableTypes = std::vector<VariableType>({ VariableType::FLOAT | VariableType::INT, VariableType::FLOAT | VariableType::INT }),
        .hasVaArgs = false,
        .minVaArgs = 0,
        .maxVaArgs = 0,
        .vaType = VariableType::ANY
    };

    auto unlimitedVaAnyNoReq = ExternalParameterInformation{
        .requiredVariableTypes = std::vector<VariableType>({}),
        .hasVaArgs = true,
        .minVaArgs = 0,
        .maxVaArgs = 999,
        .vaType = VariableType::ANY
    };

    s.setFunction("print", 
        std::make_shared<Function>(
            [&](ParameterValueList params, Stack&) {
                Array vaArgs = std::any_cast<Array>(params.back());

                std::string s = "";

                for (int i=0; i<vaArgs.size(); i++) {
                    s += ConvToString(vaArgs[i]);
                    if (i != (vaArgs.size() - 1)) s += ' ';
                }

                pf(s);

                return std::any();
            },
            unlimitedVaAnyNoReq
        )
    );

    s.setFunction("println", 
        std::make_shared<Function>(
            [&](ParameterValueList params, Stack&) {
                Array vaArgs = std::any_cast<Array>(params.back());
                std::stringstream ss;

                for (int i=0; i<vaArgs.size(); i++) {
                    ss << ConvToString(vaArgs[i]);
                    if (i != (vaArgs.size() - 1)) ss << ' ';
                }
                pf(ss.str());
                nf();

                return std::any();
            },
            unlimitedVaAnyNoReq
        )
    );

    s.setFunction("type", 
        std::make_shared<Function>(
            [&](ParameterValueList params, Stack&) { return std::string(GetVarTypeString(params[0])); },
            oneRequiredAny
        )
    );

    s.setFunction("int", 
        std::make_shared<Function>(
            [&](ParameterValueList params, Stack&) { return ConvToInt(params[0]); },
            oneRequiredAny
        )
    );

    s.setFunction("float", 
        std::make_shared<Function>(
            [&](ParameterValueList params, Stack&) { return ConvToFloat(params[0]); },
            oneRequiredAny
        )
    );

    s.setFunction("bool", 
        std::make_shared<Function>(
            [&](ParameterValueList params, Stack&) { return ConvToBool(params[0]); },
            oneRequiredAny
        )
    );

    s.setFunction("string", 
        std::make_shared<Function>(
            [&](ParameterValueList params, Stack&) { return ConvToString(params[0]); },
            oneRequiredAny
        )
    );

    s.setFunction("array", 
        std::make_shared<Function>(
            [&](ParameterValueList params, Stack&) { return ConvToBool(params[0]); },
            unlimitedVaAnyNoReq
        )
    );
    
    s.setFunction("min", std::make_shared<Function>(minFunc, twoRequiredNum));
    s.setFunction("max", std::make_shared<Function>(maxFunc, twoRequiredNum));
    s.setFunction("mod", std::make_shared<Function>(modFunc, twoRequiredNum));
    s.setFunction("randomInt", std::make_shared<Function>(randIntFunc, twoRequiredNum));
    s.setFunction("random", std::make_shared<Function>(randomFunc, noArgs));

    s.setFunction("append", 
        std::make_shared<Function>(
            appendFunc, 
            ExternalParameterInformation{
                .requiredVariableTypes = std::vector<VariableType>({ STRING | ARRAY, ANY }),
                .hasVaArgs = false,
                .minVaArgs = 0,
                .maxVaArgs = 0,
                .vaType = VariableType::ANY
            }
        )
    );

    s.setFunction("get", 
        std::make_shared<Function>(
            getFunc, 
            ExternalParameterInformation{
                .requiredVariableTypes = std::vector<VariableType>({ STRING | ARRAY, INT }),
                .hasVaArgs = false,
                .minVaArgs = 0,
                .maxVaArgs = 0,
                .vaType = VariableType::ANY
            }
        )
    );


    s.setFunction("set", 
        std::make_shared<Function>(
            setFunc,
            ExternalParameterInformation{
                .requiredVariableTypes = std::vector<VariableType>({ STRING | ARRAY, INT, ANY }),
                .hasVaArgs = false,
                .minVaArgs = 0,
                .maxVaArgs = 0,
                .vaType = VariableType::ANY
            }
        )
    );

    s.setFunction("type",
        std::make_shared<Function>(
            [&](ParameterValueList params, Stack&) {
                return String(GetVarTypeString(params[0]));
            },
            oneRequiredAny
        )
    );

    s.setFunction("ascii",
        std::make_shared<Function>(
            [&](ParameterValueList params, Stack&) {
                String s;
                s.push_back((char) std::any_cast<Int>(params[0]));
                return s;
            },
            ExternalParameterInformation{
                .requiredVariableTypes = std::vector<VariableType>({ INT }),
                .hasVaArgs = false,
                .minVaArgs = 0,
                .maxVaArgs = 0,
                .vaType = VariableType::ANY
            }
        )
    );

    s.setFunction("pop",
        std::make_shared<Function>(
            popFunc, 
            ExternalParameterInformation{
                .requiredVariableTypes = std::vector<VariableType>({ STRING | ARRAY }),
                .hasVaArgs = false,
                .minVaArgs = 0,
                .maxVaArgs = 0,
                .vaType = VariableType::ANY
            }
        )
    );

    s.setFunction("size",
        std::make_shared<Function>(
            sizeFunc, 
            ExternalParameterInformation{
                .requiredVariableTypes = std::vector<VariableType>({ STRING | ARRAY }),
                .hasVaArgs = false,
                .minVaArgs = 0,
                .maxVaArgs = 0,
                .vaType = VariableType::ANY
            }
        )
    );

    s.setFunction("erase",
        std::make_shared<Function>(
            eraseFunc, 
            ExternalParameterInformation{
                .requiredVariableTypes = std::vector<VariableType>({ STRING | ARRAY, INT, INT }),
                .hasVaArgs = false,
                .minVaArgs = 0,
                .maxVaArgs = 0,
                .vaType = VariableType::ANY
            }
        )
    );
}

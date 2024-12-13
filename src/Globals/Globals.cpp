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


void InitGlobals(Stack& s) {
    auto noArgs = ExternalFunctionParameterInformation{
        .requiredVariableTypes = std::vector<VariableType>(),
        .hasVaArgs = false,
        .minVaArgs = 0,
        .maxVaArgs = 0,
        .vaType = VariableType::ANY
    };

    auto oneRequiredAny = ExternalFunctionParameterInformation{
        .requiredVariableTypes = std::vector<VariableType>({ VariableType::ANY }),
        .hasVaArgs = false,
        .minVaArgs = 0,
        .maxVaArgs = 0,
        .vaType = VariableType::ANY
    };

    auto twoRequiredAny = ExternalFunctionParameterInformation{
        .requiredVariableTypes = std::vector<VariableType>({ VariableType::ANY, VariableType::ANY }),
        .hasVaArgs = false,
        .minVaArgs = 0,
        .maxVaArgs = 0,
        .vaType = VariableType::ANY
    };

    auto twoRequiredNum = ExternalFunctionParameterInformation{
        .requiredVariableTypes = std::vector<VariableType>({ VariableType::FLOAT | VariableType::INT, VariableType::FLOAT | VariableType::INT }),
        .hasVaArgs = false,
        .minVaArgs = 0,
        .maxVaArgs = 0,
        .vaType = VariableType::ANY
    };

    auto unlimitedVaAnyNoReq = ExternalFunctionParameterInformation{
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

                std::cout << s;

                return std::any();
            },
            unlimitedVaAnyNoReq
        )
    );

    s.setFunction("println", 
        std::make_shared<Function>(
            [&](ParameterValueList params, Stack&) {
                Array vaArgs = std::any_cast<Array>(params.back());
                std::string s = "";

                for (int i=0; i<vaArgs.size(); i++) {
                    s += ConvToString(vaArgs[i]);
                    if (i != (vaArgs.size() - 1)) s += ' ';
                }
                std::cout << s << '\n';

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
    
    s.setFunction("append", 
        std::make_shared<Function>(
            appendFunc, 
            ExternalFunctionParameterInformation{
                .requiredVariableTypes = std::vector<VariableType>({ VariableType::STRING | VariableType::ARRAY, VariableType::ANY }),
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
            ExternalFunctionParameterInformation{
                .requiredVariableTypes = std::vector<VariableType>({ VariableType::STRING | VariableType::ARRAY, VariableType::INT }),
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
            ExternalFunctionParameterInformation{
                .requiredVariableTypes = std::vector<VariableType>({ VariableType::STRING | VariableType::ARRAY, VariableType::INT, VariableType::ANY }),
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
            ExternalFunctionParameterInformation{
                .requiredVariableTypes = std::vector<VariableType>({ VariableType::INT }),
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
            ExternalFunctionParameterInformation{
                .requiredVariableTypes = std::vector<VariableType>({ VariableType::STRING | VariableType::ARRAY }),
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
            ExternalFunctionParameterInformation{
                .requiredVariableTypes = std::vector<VariableType>({ VariableType::STRING | VariableType::ARRAY }),
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
            ExternalFunctionParameterInformation{
                .requiredVariableTypes = std::vector<VariableType>({ VariableType::STRING | VariableType::ARRAY, VariableType::INT, VariableType::INT }),
                .hasVaArgs = false,
                .minVaArgs = 0,
                .maxVaArgs = 0,
                .vaType = VariableType::ANY
            }
        )
    );
}

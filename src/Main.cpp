#include "Interpreter/Interpreter.hpp"

#include "CLI11.hpp"

#ifdef Emscripten

extern void outputFunc(std::string s);
extern void newline(std::string s);

HourInterpreter interp;

extern "C" execCode(std::string c) {
    interp.execCode(c);
}

extern "C" resetInterpreter() {
    interp.reset();
    interp.addGlobals(outputFunc, newline);
}

int main() {
    resetInterpreter();

    return 0;
}

#endif

#ifndef Emscripten

#include <iostream>

void print(std::string s) {
    std::cout << s;
}

void newline() {
    std::cout << '\n';
}

int main(int argc, char** argv) {
    CLI::App app{"Hour Language Interpreter"};

    std::string file;
    auto interpret = app.add_option("-i,--interpret", file, "Execute a file")->type_name("FILE");

    int debugLevel = 0;
    auto debug = app.add_option("-d,--debug", debugLevel, "Set the debug level")->type_name("0, 1, 2");

    CLI11_PARSE(app, argc, argv);

    if (interpret->count() > 0) {
        HourInterpreter interp;

        interp.setDebugLevel(debugLevel);

        interp.addGlobals(print, newline);
        interp.execFile(file);

        exit(0);
    }

    HourInterpreter interp;
    interp.addGlobals(
        [](std::string s) {
            std::cout << s;
        },
        []() {
            std::cout << '\n';
        }
    );

    interp.getStack().setFunction(
        "exit",
        std::make_shared<Function>(
            [&](ParameterValueList params, Stack& s) {
                exit(0);

                return std::any();
            },
            ExternalParameterInformation {
                .requiredVariableTypes = std::vector<VariableType>(),
                .hasVaArgs = false
            }
        )    
    );

    std::cout << "Entering REPL\n";
    std::cout << "Type exit() to quit!\n";
    std::cout << "Semicolons are required!\n\n";

    // REPL
    while(true) {
        // Run REPL
        std::string line;
        std::cout << "> ";
        std::getline(std::cin, line);

        interp.execCode(line);
    }

    return 0;
}
#endif
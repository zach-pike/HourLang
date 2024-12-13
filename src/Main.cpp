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


int main(int argc, char** argv) {
    CLI::App app{"Hour Language Interpreter"};

    std::string file;
    auto interpret = app.add_option("-i,--interpret", file, "Execute a file")->type_name("FILE");

    std::vector<std::string> paths;
    auto addModulePathOpt = app.add_option("-p,--path", paths, "Add a additional module path")->type_name("Path");

    int debugLevel = 0;
    auto debug = app.add_option("-d,--debug", debugLevel, "Set the debug level")->type_name("0, 1, 2");

    CLI11_PARSE(app, argc, argv);

    HourInterpreter interp;
    interp.setDebugLevel(debugLevel);
    interp.addGlobals();

    // Add default library folder
    interp.getStack().addModulePath(std::filesystem::current_path() / "libraries");

    for (auto modPath : paths) {
        auto fp = std::filesystem::absolute(modPath);

        if (!std::filesystem::is_directory(fp)) throw std::runtime_error("Provided path is not a directory!");
        interp.getStack().addModulePath(fp);
    }

    // Interpret function
    if (interpret->count() > 0) {
        interp.execFile(file);

        exit(0);
    }
    
    // If we get here then we are not interpreting any files, therefore we will start a repl

    // Exit function
    interp.getStack().setFunction(
        "exit",
        std::make_shared<Function>(
            [&](ParameterValueList params, Stack& s) {
                exit(0);

                return std::any();
            },
            ExternalFunctionParameterInformation {
                .requiredVariableTypes = std::vector<VariableType>(),
                .hasVaArgs = false
            }
        )    
    );

    // Welcome message
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
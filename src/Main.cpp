#include "Interpreter/Interpreter.hpp"

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
    std::vector<std::string> args;

    for (int i=0; i<argc; i++) {
        args.push_back(std::string(argv[i]));
    }

    HourInterpreter interp;
        interp.addGlobals(print, newline);
        interp.execFile(".\\examples\\brainf.hc");

    return 0;
}
#endif
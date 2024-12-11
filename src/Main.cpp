#include "Interpreter/Interpreter.hpp"

int main(int argc, char** argv) {
    HourInterpreter interp;
    interp.addGlobals();
    interp.execFile("examples/test.hc");

    return 0;
}
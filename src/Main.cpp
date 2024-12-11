#include "Interpreter/Interpreter.hpp"

int main(int argc, char** argv) {
    HourInterpreter interp;
    interp.addGlobals();
    // interp.execFile("examples/fibonacci.hc");
    interp.execFile("examples/brainf.hc");

    return 0;
}
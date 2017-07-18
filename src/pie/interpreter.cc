#include <Python.h>

struct Interpreter {
    Interpreter() {
        Py_Initialize();
    }

    ~Interpreter() {
        Py_Finalize();
    }
};

Interpreter interpreter;

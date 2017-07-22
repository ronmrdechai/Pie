#include <Python.h>

struct Interpreter {
    Interpreter() : should_finalize(false) {
        if (!Py_IsInitialized()) {
            Py_Initialize();
            should_finalize = true;
        }
    }

    ~Interpreter() {
        if (should_finalize) {
            Py_Finalize();
        }
    }

    bool should_finalize;
};

Interpreter interpreter;

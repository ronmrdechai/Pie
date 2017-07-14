#include <Python.h>

struct setup {
    setup() {
        Py_Initialize();
    }

    ~setup() {
        Py_Finalize();
    }
};

setup s;

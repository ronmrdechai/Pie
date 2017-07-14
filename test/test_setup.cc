#include <Python.h>

struct Setup {
    Setup() {
        Py_Initialize();
    }

    ~Setup() {
        Py_Finalize();
    }
};

Setup setup;

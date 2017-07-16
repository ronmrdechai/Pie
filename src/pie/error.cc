#include "error.h"

#include <sstream>
#include <iostream>

namespace pie {

void error::throw_exception() {
    PyObject* type;
    PyObject* err;
    PyObject* traceback;
    PyErr_Fetch(&type, &err, &traceback);

    object type_o      = type;
    object err_o       = err;
    object traceback_o = traceback;

    std::ostringstream ss;
    ss << ((PyTypeObject*)type)->tp_name << ": " << err_o;

    throw error(type_o, err_o, traceback_o, ss.str());
}

void error::conditional_throw() {
    PyObject* occurred = PyErr_Occurred();
    if (occurred) {
        throw_exception();
    }
}

const object& error::type() const {
    return m_type;
}

const object& error::traceback() const {
    return m_traceback;
}

error::error(const object& type, 
             const object& error,
             const object& traceback,
             const std::string& what_arg) :
    object(error),
    std::runtime_error(what_arg),
    m_type(type),
    m_traceback(traceback) { }

} // namespace pie

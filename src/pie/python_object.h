#pragma once

#include "parse.h"

namespace pie {

class python_object {
public:
    python_object();
    explicit python_object(PyObject* o);
    template <typename... Args>
    explicit python_object(Args&&... args);

// Non-Python methods

    /// Access the underlying pointer
    PyObject* get();
    /// Access the underlying pointer
    PyObject* operator->();

private:
    PyObject* m_obj;
};

} // namespace pie

#include "python_object.inl"

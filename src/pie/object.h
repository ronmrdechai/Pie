#pragma once

#include "parse.h"

namespace pie {

class object {
public:
    object();
    explicit object(PyObject* o);
    template <typename... Args>
    explicit object(Args&&... args);

// Non-Python methods

    /// Access the underlying pointer
    PyObject* get();
    /// Access the underlying pointer
    PyObject* operator->();

private:
    PyObject* m_obj;
};

} // namespace pie

#include "object.inl"

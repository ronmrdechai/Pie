#pragma once

#include <Python.h>

namespace pie {

class object {
public:
    object();
    ~object();

    object(PyObject* o);
    template <typename... Args>
    object(Args&&... args);

    object(object& other);
    object(object&& other);
    object(const object& other);

    object& operator=(object other);

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

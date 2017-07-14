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

    // __repr__
    // __str__
    // __bytes__
    // __lt__
    // __le__
    // __eq__
    // __ne__
    // __gt__
    // __ge__
    // __hash__
    // __bool__

    // __call__

    // __len__
    // __getitem__
    // __setitem__
    // __delitem__
    // __contains__

    // __add__
    // __iadd__
    // __sub__
    // __isub__
    // __mul__
    // __imul__
    // __truediv__
    // __itruediv__
    // __mod__
    // __imod__
    // __pow__
    // __ipow__
    // __lshift__
    // __ilshift__
    // __rshift__
    // __irshift__
    // __and__
    // __iand__
    // __xor__
    // __ixor__
    // __or__
    // __ior__

    // __neg__
    // __pos__
    // __abs__
    // __invert__

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

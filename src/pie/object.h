#pragma once

#include <Python.h>
#include <ostream>

namespace pie {

class object {
    struct proxy {
        proxy(const object& o, const object& i);
        proxy& operator=(const object& item);

        const object& o;
        const object& i;
    };

public:
    object();
    ~object();

    object(PyObject* o);
    template <typename... Args>
    object(Args&&... args);

    object(object& other);
    object(object&& other);
    object(const object& other);

    object(proxy other);

    object& operator=(object other);

    // __repr__
    object repr() const;
    // __str__
    // __bytes__
    object str() const;
    // __lt__
    object operator< (const object& other) const;
    // __le__
    object operator<=(const object& other) const;
    // __eq__
    object operator==(const object& other) const;
    // __ne__
    object operator!=(const object& other) const;
    // __gt__
    object operator> (const object& other) const;
    // __ge__
    object operator>=(const object& other) const;
    // __hash__
    ssize_t hash() const;
    // __bool__
    operator bool() const;

    // __call__
    template <typename... Args>
    object operator()(Args&&... args) const;

    // __len__
    ssize_t length() const;
    // __getitem__
    const proxy operator[](const object& item) const;
    // __setitem__
    proxy operator[](const object& item);

    // __add__
    // __iadd__
    object  operator+ (const object& other) const;
    object& operator+=(const object& other);
    // __sub__
    // __isub__
    object  operator- (const object& other) const;
    object& operator-=(const object& other);
    // __mul__
    // __imul__
    object  operator* (const object& other) const;
    object& operator*=(const object& other);
    // __truediv__
    // __itruediv__
    object  operator/ (const object& other) const;
    object& operator/=(const object& other);
    // __mod__
    // __imod__
    object  operator% (const object& other) const;
    object& operator%=(const object& other);
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
    PyObject* get() const;
    /// Access the underlying pointer
    PyObject* operator->() const;

private:
    PyObject* m_obj;
};

// __getattr__
// __setattr__
// __hasattr__

std::ostream& operator<<(std::ostream& os, const object& o);

} // namespace pie

#include "object.inl"

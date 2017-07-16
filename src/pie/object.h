#pragma once

#include <Python.h>
#include <ostream>

namespace pie {
namespace detail {

struct iterator;

} // namespace detail

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
    object str() const;
    // __bytes__
    object bytes() const;
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
    explicit operator bool() const;

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
    object  operator+ (const object& other) const;
    // __iadd__
    object& operator+=(const object& other);
    // __sub__
    object  operator- (const object& other) const;
    // __isub__
    object& operator-=(const object& other);
    // __mul__
    object  operator* (const object& other) const;
    // __imul__
    object& operator*=(const object& other);
    // __truediv__
    object  operator/ (const object& other) const;
    // __itruediv__
    object& operator/=(const object& other);
    // __mod__
    object  operator% (const object& other) const;
    // __imod__
    object& operator%=(const object& other);

    // __lshift__
    object  operator<< (const object& other) const;
    // __ilshift__
    object& operator<<=(const object& other);
    // __rshift__
    object  operator>> (const object& other) const;
    // __irshift__
    object& operator>>=(const object& other);
    // __and__
    object  operator& (const object& other) const;
    // __iand__
    object& operator&=(const object& other);
    // __xor__
    object  operator^ (const object& other) const;
    // __ixor__
    object& operator^=(const object& other);
    // __or__
    object  operator| (const object& other) const;
    // __ior__
    object& operator|=(const object& other);

    // __neg__
    object operator-() const;
    // __pos__
    object operator+() const;
    // __invert__
    object operator~() const;

    detail::iterator begin();
    detail::iterator end();

// Non-Python methods

    /// Access the underlying pointer
    PyObject* get() const;
    /// Access the underlying pointer
    PyObject* operator->() const;

private:
    PyObject* m_obj;
};

detail::iterator begin(object&& o);
detail::iterator end(object&& o);

// __getattr__
object getattr(const object& o, const object& attr);
// __setattr__
object setattr(object& o, const object& attr, const object& value);
// __hasattr__
bool hasattr(const object& o, const object& attr);

// print
std::ostream& operator<<(std::ostream& os, const object& o);

object pow(const object& b, const object& e, const object& o = Py_None);
object abs(const object& o);

namespace detail {

struct iterator : std::iterator<std::input_iterator_tag, object> {
    iterator(object o, ssize_t i);
    iterator(const iterator& other);

    iterator& operator++();
    iterator operator++(int);

    bool operator==(const iterator& other);
    bool operator!=(const iterator& other);

    object operator*();

    object o;
    ssize_t i;
};

} // namespace detail

} // namespace pie

#include "object.inl"

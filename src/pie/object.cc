#include "object.h"

#include <string_view>

namespace pie {

object::object() : m_obj(nullptr) { }

object::~object() {
    if (m_obj) {
        Py_DECREF(m_obj);
    }
}

object::object(PyObject* o) : m_obj(o) {
    if (m_obj == nullptr) {
        throw std::runtime_error("object initialized with nullptr");
    }
}

object::object(object& other) : object(static_cast<object const&>(other)) { }

object::object(object&& other) : m_obj(other.m_obj) {
    other.m_obj = nullptr;
}

object::object(const object& other) : m_obj(other.m_obj) {
    Py_INCREF(m_obj);
}

object::object(proxy other) : object(PyObject_GetItem(other.o.m_obj,
                                                      other.i.m_obj)) { }

object& object::operator=(object other) {
    std::swap(m_obj, other.m_obj);
    return *this;
}

object object::repr() const {
    return PyObject_Repr(m_obj);
}

object object::str() const {
    return PyObject_Str(m_obj);
}

object object::operator< (const object& other) const {
    return PyObject_RichCompare(m_obj, other.m_obj, Py_LT);
}

object object::operator<=(const object& other) const {
    return PyObject_RichCompare(m_obj, other.m_obj, Py_LE);
}

object object::operator==(const object& other) const {
    return PyObject_RichCompare(m_obj, other.m_obj, Py_EQ);
}

object object::operator!=(const object& other) const {
    return PyObject_RichCompare(m_obj, other.m_obj, Py_NE);
}

object object::operator> (const object& other) const {
    return PyObject_RichCompare(m_obj, other.m_obj, Py_GT);
}

object object::operator>=(const object& other) const {
    return PyObject_RichCompare(m_obj, other.m_obj, Py_GE);
}

ssize_t object::hash() const {
    return PyObject_Hash(m_obj);
}

object::operator bool() const {
    return PyObject_IsTrue(m_obj);
}

ssize_t object::length() const {
    return PyObject_Length(m_obj);
}

const object::proxy object::operator[](const object& item) const {
    return proxy(*this, item);
}

object::proxy object::operator[](const object& item) {
    return proxy(*this, item);
}

PyObject* object::get() const {
    return m_obj;
}

PyObject* object::operator->() const {
    return get();
}

object::proxy::proxy(const object& o, const object& i) : o(o), i(i) { }

object::proxy& object::proxy::operator=(const object& item) {
    PyObject_SetItem(o.m_obj, i.m_obj, item.m_obj);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const object& o) {
    object str = o.str();
    object ascii = PyUnicode_AsASCIIString(str.get());
    const char* data = PyBytes_AsString(ascii.get());
    ssize_t size = PyBytes_Size(ascii.get());
    os << std::string_view(data, size);
    return os;
}

} // namespace pie

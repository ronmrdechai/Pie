#include "object.h"
#include "error.h"

#include <string_view>

namespace pie {

object::object() : m_obj(nullptr) { }

object::~object() {
    if (m_obj) {
        Py_DECREF(m_obj);
    }
}

object::object(PyObject* o) : m_obj(o) {
    error::conditional_throw();
}

object::object(object& other) : object(static_cast<object const&>(other)) { }

object::object(object&& other) : m_obj(other.m_obj) {
    other.m_obj = nullptr;
}

object::object(const object& other) : m_obj(other.m_obj) {
    if (m_obj) {
        Py_INCREF(m_obj);
    }
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

object object::bytes() const {
    return PyObject_Bytes(m_obj);
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

object object::operator+ (const object& other) const {
    return PyNumber_Add(m_obj, other.m_obj);
}

object& object::operator+=(const object& other) {
    *this = PyNumber_InPlaceAdd(m_obj, other.m_obj);
    return *this;
}

object object::operator- (const object& other) const {
    return PyNumber_Subtract(m_obj, other.m_obj);
}

object& object::operator-=(const object& other) {
    *this = PyNumber_InPlaceSubtract(m_obj, other.m_obj);
    return *this;
}

object object::operator* (const object& other) const {
    return PyNumber_Multiply(m_obj, other.m_obj);
}

object& object::operator*=(const object& other) {
    *this = PyNumber_InPlaceMultiply(m_obj, other.m_obj);
    return *this;
}

object object::operator/ (const object& other) const {
    return PyNumber_TrueDivide(m_obj, other.m_obj);
}

object& object::operator/=(const object& other) {
    *this = PyNumber_InPlaceTrueDivide(m_obj, other.m_obj);
    return *this;
}

object object::operator% (const object& other) const {
    return PyNumber_Remainder(m_obj, other.m_obj);
}

object& object::operator%=(const object& other) {
    *this = PyNumber_InPlaceRemainder(m_obj, other.m_obj);
    return *this;
}

object object::operator<< (const object& other) const {
    return PyNumber_Lshift(m_obj, other.m_obj);
}

object& object::operator<<=(const object& other) {
    *this = PyNumber_InPlaceLshift(m_obj, other.m_obj);
    return *this;
}

object object::operator>> (const object& other) const {
    return PyNumber_Rshift(m_obj, other.m_obj);
}

object& object::operator>>=(const object& other) {
    *this = PyNumber_InPlaceRshift(m_obj, other.m_obj);
    return *this;
}

object object::operator& (const object& other) const {
    return PyNumber_And(m_obj, other.m_obj);
}

object& object::operator&=(const object& other) {
    *this = PyNumber_InPlaceAnd(m_obj, other.m_obj);
    return *this;
}

object object::operator^ (const object& other) const {
    return PyNumber_Xor(m_obj, other.m_obj);
}

object& object::operator^=(const object& other) {
    *this = PyNumber_InPlaceXor(m_obj, other.m_obj);
    return *this;
}

object object::operator| (const object& other) const {
    return PyNumber_Or(m_obj, other.m_obj);
}

object& object::operator|=(const object& other) {
    *this = PyNumber_InPlaceOr(m_obj, other.m_obj);
    return *this;
}

object object::operator-() const {
    return PyNumber_Negative(m_obj);
}

object object::operator+() const {
    return PyNumber_Positive(m_obj);
}

object object::operator~() const {
    return PyNumber_Invert(m_obj);
}

iterator object::begin() {
    if (PySequence_Check(m_obj)) {
        return iterator(*this, 0);
    }
    throw std::runtime_error("object is not a sequence");
}

iterator object::end() {
    if (PySequence_Check(m_obj)) {
        ssize_t size = PySequence_Length(m_obj);
        return iterator(*this, size);
    }
    throw std::runtime_error("object is not a sequence");
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

object getattr(const object& o, const object& attr) {
    return PyObject_GetAttr(o.get(), attr.get());
}

object setattr(object& o, const object& attr, const object& value) {
    return PyObject_SetAttr(o.get(), attr.get(), value.get());
}

bool hasattr(const object& o, const object& attr) {
    return PyObject_HasAttr(o.get(), attr.get());
}

object pow(const object& b, const object& e, const object& o) {
    return PyNumber_Power(b.get(), e.get(), o.get());
}

object abs(const object& o) {
    return PyNumber_Absolute(o.get());
}

iterator begin(object&& o) {
    return o.begin();
}

iterator end(object&& o) {
    return o.end();
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

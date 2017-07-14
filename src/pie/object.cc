#include "object.h"

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

object& object::operator=(object other) {
    std::swap(m_obj, other.m_obj);
    return *this;
}

PyObject* object::get() {
    return m_obj;
}

PyObject* object::operator->() {
    return get();
}

} // namespace pie

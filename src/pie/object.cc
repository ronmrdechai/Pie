#include "object.h"

namespace pie {

object::object() : m_obj(nullptr) { }

object::object(PyObject* o) : m_obj(o) {
    if (m_obj == nullptr) {
        // TODO: wrap PyErr
        throw std::runtime_error("object initialized with nullptr");
    }
}

} // namespace pie

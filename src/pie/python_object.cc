#include "python_object.h"

namespace pie {

python_object::python_object() : m_obj(nullptr) { }

python_object::python_object(PyObject* o) : m_obj(o) {
    if (m_obj == nullptr) {
        // TODO: wrap PyErr
        throw std::runtime_error("python_object initialized with nullptr");
    }
}

} // namespace pie

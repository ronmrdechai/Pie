#include "parse.h"

namespace pie {

template <typename... Args>
object::object(Args&&... args) :
    object(parse_object(std::forward<Args>(args)...)) { }

template <typename... Args>
object object::operator()(Args&&... args) const {
    object args_tuple = parse_object(
            std::make_tuple<Args...>(std::forward<Args>(args)...));
    return PyObject_CallObject(m_obj, args_tuple.get());
}

} // namespace pie

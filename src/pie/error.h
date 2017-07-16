#include <stdexcept>

#include "object.h"

namespace pie {

class error : public object, public std::runtime_error {
public:
    static void throw_exception();
    static void conditional_throw();

    const object& type() const;
    const object& traceback() const;

private:
    error(const object& type, 
          const object& error,
          const object& traceback,
          const std::string& what_arg);
    object m_type;
    object m_traceback;
};

} // namespace pie

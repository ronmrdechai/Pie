#include "iterator.h"

namespace pie {

iterator::iterator(object o, ssize_t i) : o(o), i(i) { }
iterator::iterator(const iterator& other) : 
    iterator(other.o, other.i) { }

iterator& iterator::operator++() {
    ++i;
    return *this;
}

iterator iterator::operator++(int) {
    iterator temp(*this);
    operator++();
    return temp;
}

bool iterator::operator==(const iterator& other) {
    return (o.get() == other.o.get()) && (i == other.i);
}

bool iterator::operator!=(const iterator& other) {
    return !((*this) == other);
}

object iterator::operator*() {
    return PySequence_GetItem(o.get(), i);
}

} // namespace pie

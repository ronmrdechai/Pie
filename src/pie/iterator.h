#pragma once

#include <iterator>

#include "object.h"

namespace pie {

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

} // namespace pie


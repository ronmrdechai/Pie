#pragma once

#include <Python.h>

namespace pie {

template <typename T>
PyObject* parse_object(T&& t);

} // namespace pie

#include "parse.inl"

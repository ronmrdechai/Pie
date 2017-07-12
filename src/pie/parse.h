#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wregister"
#include <Python.h>
#pragma GCC diagnostic pop

namespace pie {

template <typename T>
PyObject* parse_object(T&& t);

template <typename T, typename... Ts>
PyObject* parse_object(T&& t, Ts&&... ts);

} // namespace pie

#include "parse.inl"

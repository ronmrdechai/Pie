#pragma once

#include <Python.h>

namespace pie {

template <typename T>
PyObject* parse_object(T&& t);

template <typename T, typename... Ts>
PyObject* parse_object(T&& t, Ts&&... ts);

} // namespace pie

#include "parse.inl"

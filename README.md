# Pie #

Welcome to **Pie**, a wrapper for CPython's C API in C++.

CPython's C API is really nice when writing C, but when writing C++ it leaves
much to be desired. The API passes around `PyObject*` objects between functions
in an object oriented fashion. **Pie** wraps Python's `PyObject*` with its own
`object` class, it leverages C++'s operator overloading to call CPython API
functions on the `PyObject*` and it automatically keeps track of the object's
reference count using constructors and destructors. **Pie** can also parse
certain C++ objects into Python objects, for example, vectors turn into lists,
maps turn into dictionaries, etc.

## Features ##

1. An idiomatic C++ wrapper around `PyObject*` objects, using classes and
   operator overloading.
1. Automatic incrementing and decrementing of `PyObject*` reference counts.
1. Parsing of C++ types into Python objects.
1. Wrapping of Python exceptions into C++ exceptions.

## Usage ##

See the [example](https://github.com/ronmrdechai/Pie#example) for more
information on how to use **Pie**. Just link with `libpie` and you should be
ready to go.

> _Note:_ **Pie** is not a replacement for the CPython API, it is intended to
> compliment it and make it easier to use in C++.

### Setup ###

CPython requires you call `Py_Initialize` before you start working with its
types, and `Py_Finalize` when you are done. Because **Pie** is only a thin
wrapper around CPython, you are required to call these functions yourself
as well.

A common error is a segfault right after you call `Py_Finalize` at the end of a
scope containing a `pie::object`. Note that the object's destructor is called
after the scope exits, thus it is called after `Py_Finalize`, causing a
segfault. Do not call `Py_Finalize` in a scope containing `pie::objects`.

## The Parser ##

**Pie's** C++ type parser is very simple, it handles the following cases:

1. C integers become Python integers.
1. C strings (`const char *`) become Python strings.
1. C++ strings (`std::string`) become Python strings.
1. Container types with an `std::pair` value type become Python dictionaries.
1. Container types without an `std::pair` value type become Python lists.

## Python Version ##

**Pie** currently works on with Python 3 only. There are plans to port **Pie**
to Python 2 in the future.

## Building ##

**Pie** requires the following:

1. Compiler with C++17 (gcc-7 should work fine).
1. Python 3 and development headers.
1. CMake version 3+

The build process clones and builds 
[googletest](https://github.com/google/googletest) which is used to run the
tests. To build issue the following:

```bash
git clone git@github.com:ronmrdechai/Pie.git
mkdir build
cd build
cmake ..
make
sudo make install
```

## Platforms ##

**Pie** is developed and tested on macOS but should work on any platform with
Python and C++17.

## Example ##

See [tests](test/test_object.cc) for more detailed examples.

```c++
#include <pie/pie.h>                   

#include <iostream>                    

int main() {                           
    Py_Initialize();                   

    {                                  
        pie::object os = PyImport_ImportModule("os");                          
        pie::object os_environ = pie::getattr(os, "environ");                  

        std::cout << "The following directories are in the PATH:" << std::endl;                                                                                
        for (auto dir: getattr(os_environ["PATH"], "split")(":")) {            
            std::cout << dir << std::endl;                                     
        }                              

        pie::object zero = 0;          
        pie::object one = 1;           
        try {                          
            one / zero;                
        } catch (pie::error& e) {      
            std::cout << "Caught Python exception:" << std::endl;              
            std::cout << e.what() << std::endl;                                
        }                              
    }                                  

    Py_Finalize();                     
    return 0;                          
}
```

## Why not Boost.Python, PyBind11 or SWIG? ##

Boost.Python, PyBind11 and SWIG are wonderful packages, but they different from
**Pie**. These packages wrap C++ classes and functions into Python classes and 
functions, allowing you call them from Python. Some of them have support for
calling Python code from C++, but this functionality has been added as an
afterthought. 

**Pie** has been built from the ground up to wrap Python objects into C++
objects, allowing you to easily call Python from your C++ code, and embed it in
your applications.

## To Do ##

- [ ] Provide a complete documentation for **Pie**
- [ ] Wrap Python builtin types with `pie::objects`.

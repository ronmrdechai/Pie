#include <string>
#include <vector>
#include <deque>
#include <set>
#include <map>

#include <catch.hpp>
#include <pie/parse.h>

using pie::parse_object;

TEST_CASE("Numbers are parsed", "[parse_object]") {
    Py_Initialize();

    SECTION("char") {
        char i = 1;
        PyObject* o = parse_object(i);
        REQUIRE(PyNumber_Check(o));
        REQUIRE(1 == PyNumber_AsSsize_t(o, nullptr));
    }
    SECTION("short") {
        short i = 2;
        PyObject* o = parse_object(i);
        REQUIRE(PyNumber_Check(o));
        REQUIRE(2 == PyNumber_AsSsize_t(o, nullptr));
    }
    SECTION("int") {
        int i = 3;
        PyObject* o = parse_object(i);
        REQUIRE(PyNumber_Check(o));
        REQUIRE(3 == PyNumber_AsSsize_t(o, nullptr));
    }
    SECTION("long") {
        long i = 4;
        PyObject* o = parse_object(i);
        REQUIRE(PyNumber_Check(o));
        REQUIRE(4 == PyNumber_AsSsize_t(o, nullptr));
    }
    SECTION("float") {
        float i = 0.1f;
        PyObject* o = parse_object(i);
        REQUIRE(PyNumber_Check(o));
        REQUIRE(0.1f == PyFloat_AsDouble(o));
    }
    SECTION("double") {
        double i = 0.2;
        PyObject* o = parse_object(i);
        REQUIRE(PyNumber_Check(o));
        REQUIRE(0.2 == PyFloat_AsDouble(o));
    }

    Py_Finalize();
}

#include <iostream>

TEST_CASE("strings are parsed", "[parse_object]") {
    Py_Initialize();

    std::string foobar = "foobar";
    SECTION("const char*") {
        const char* s = "foobar";
        PyObject* o = parse_object(s);
        REQUIRE(PyBytes_Check(o));
        REQUIRE(foobar == PyBytes_AsString(o));
    }
    SECTION("char[]") {
        char s[7] = "foobar";
        PyObject* o = parse_object(s);
        REQUIRE(PyBytes_Check(o));
        CHECK(foobar == PyBytes_AsString(o));
    }
    SECTION("std::string") {
        std::string s = "foobar";
        PyObject* o = parse_object(s);
        REQUIRE(PyBytes_Check(o));
        CHECK(foobar == PyBytes_AsString(o));
    }
    SECTION("literal") {
        PyObject* o = parse_object("foobar");
        REQUIRE(PyBytes_Check(o));
        CHECK(foobar == PyBytes_AsString(o));
    }

    Py_Finalize();
}

TEST_CASE("sequences are parsed", "[parse_object]") {
    Py_Initialize();

    SECTION("std::vector") {
        std::vector<int> v{1, 2, 3, 4, 5};
        PyObject* o = parse_object(v);
        REQUIRE(PySequence_Check(o));
        REQUIRE(5 == PySequence_Length(o));
        for (ssize_t i = 0; i < PySequence_Length(o); ++i) {
            REQUIRE(i + 1 == 
                PyNumber_AsSsize_t(PySequence_GetItem(o, i), nullptr));
        }
    }
    SECTION("std::deque") {
        std::deque<int> v{1, 2, 3, 4, 5};
        PyObject* o = parse_object(v);
        REQUIRE(PySequence_Check(o));
        REQUIRE(5 == PySequence_Length(o));
        for (ssize_t i = 0; i < PySequence_Length(o); ++i) {
            REQUIRE(i + 1 == 
                PyNumber_AsSsize_t(PySequence_GetItem(o, i), nullptr));
        }
    }
    SECTION("std::set") {
        std::set<int> v{1, 2, 3, 4, 5};
        PyObject* o = parse_object(v);
        REQUIRE(PySequence_Check(o));
        REQUIRE(5 == PySequence_Length(o));
        for (ssize_t i = 0; i < PySequence_Length(o); ++i) {
            REQUIRE(i + 1 == 
                PyNumber_AsSsize_t(PySequence_GetItem(o, i), nullptr));
        }
    }

    Py_Finalize();
}

TEST_CASE("maps are parsed", "[parse_object]") {
    Py_Initialize();

    SECTION("std::map") {
        std::map<std::string, int> m{ {"foo", 1}, {"bar", 2} };
        PyObject* o = parse_object(m);
        REQUIRE(PyDict_Check(o));
        REQUIRE(1 == PyNumber_AsSsize_t(PyDict_GetItem(o, parse_object("foo")),
                                        nullptr));
        REQUIRE(2 == PyNumber_AsSsize_t(PyDict_GetItem(o, parse_object("bar")),
                                        nullptr));
    }
    SECTION("std::multimap") {
        std::multimap<std::string, int> m{ {"foo", 1}, {"bar", 2} };
        PyObject* o = parse_object(m);
        REQUIRE(PyDict_Check(o));
        REQUIRE(1 == PyNumber_AsSsize_t(PyDict_GetItem(o, parse_object("foo")),
                                        nullptr));
        REQUIRE(2 == PyNumber_AsSsize_t(PyDict_GetItem(o, parse_object("bar")),
                                        nullptr));
    }

    Py_Finalize();
}

TEST_CASE("tuples are parsed", "[parse_object]") {
    Py_Initialize();

    SECTION("std::tuple") {
        std::tuple<int, int, std::string> t{1, 2, "foobar"};
        PyObject* o = parse_object(t);
        REQUIRE(PyTuple_Check(o));
        REQUIRE(1 == PyNumber_AsSsize_t(PyTuple_GetItem(o, 0),
                                        nullptr));
        REQUIRE(2 == PyNumber_AsSsize_t(PyTuple_GetItem(o, 1),
                                        nullptr));
        REQUIRE(std::string("foobar") == 
            PyBytes_AsString(PyTuple_GetItem(o, 2)));
    }

    SECTION("std::make_tuple") {
        PyObject* o = parse_object(std::make_tuple<int, int, std::string>
                (1, 2, "foobar"));
        REQUIRE(PyTuple_Check(o));
        REQUIRE(1 == PyNumber_AsSsize_t(PyTuple_GetItem(o, 0),
                                        nullptr));
        REQUIRE(2 == PyNumber_AsSsize_t(PyTuple_GetItem(o, 1),
                                        nullptr));
        REQUIRE(std::string("foobar") == 
            PyBytes_AsString(PyTuple_GetItem(o, 2)));
    }

    Py_Finalize();
}

TEST_CASE("multiple arguments are parsed", "[parse_object]") {
    Py_Initialize();

    SECTION("same type") {
        PyObject* o = parse_object(1, 2, 3);
        REQUIRE(PySequence_Check(o));
        REQUIRE(3 == PySequence_Length(o));
        for (ssize_t i = 0; i < PySequence_Length(o); ++i) {
            REQUIRE(i + 1 == 
                PyNumber_AsSsize_t(PySequence_GetItem(o, i), nullptr));
        }
    }

    SECTION("different types") {
        PyObject* o = parse_object(1, std::vector<int>{2, 3, 4}, 
                                      std::map<int, int>{ {5, 6}, {7, 8} });
        REQUIRE(PySequence_Check(o));
        REQUIRE(3 == PySequence_Length(o));

        REQUIRE(PyNumber_Check(PySequence_GetItem(o, 0)));
        REQUIRE(PySequence_Check(PySequence_GetItem(o, 1)));
        REQUIRE(PyDict_Check(PySequence_GetItem(o, 2)));
    }

    Py_Finalize();
}

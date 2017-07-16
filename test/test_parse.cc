#include <string>
#include <vector>
#include <deque>
#include <set>
#include <map>

#include <pie/parse.h>
#include <gtest/gtest.h>

using pie::parse_object;

TEST(parse, numbers) {
    {
        char i = 1;
        PyObject* o = parse_object(i);
        EXPECT_TRUE(PyNumber_Check(o));
        EXPECT_EQ(1, PyNumber_AsSsize_t(o, nullptr));
    }
    {
        short i = 2;
        PyObject* o = parse_object(i);
        EXPECT_TRUE(PyNumber_Check(o));
        EXPECT_EQ(2, PyNumber_AsSsize_t(o, nullptr));
    }
    {
        int i = 3;
        PyObject* o = parse_object(i);
        EXPECT_TRUE(PyNumber_Check(o));
        EXPECT_EQ(3, PyNumber_AsSsize_t(o, nullptr));
    }
    {
        long i = 4;
        PyObject* o = parse_object(i);
        EXPECT_TRUE(PyNumber_Check(o));
        EXPECT_EQ(4, PyNumber_AsSsize_t(o, nullptr));
    }
    {
        float i = 0.1f;
        PyObject* o = parse_object(i);
        EXPECT_TRUE(PyNumber_Check(o));
        EXPECT_EQ(0.1f, PyFloat_AsDouble(o));
    }
    {
        double i = 0.2;
        PyObject* o = parse_object(i);
        EXPECT_TRUE(PyNumber_Check(o));
        EXPECT_EQ(0.2, PyFloat_AsDouble(o));
    }
}

TEST(parse, strings) {
    std::string foobar = "foobar";
    {
        const char* s = "foobar";
        PyObject* o = parse_object(s);
        EXPECT_TRUE(PyUnicode_Check(o));
        EXPECT_STREQ("foobar", PyBytes_AsString(PyUnicode_AsASCIIString(o)));
    }
    {
        char s[7] = "foobar";
        PyObject* o = parse_object(s);
        EXPECT_TRUE(PyUnicode_Check(o));
        EXPECT_STREQ("foobar", PyBytes_AsString(PyUnicode_AsASCIIString(o)));
    }
    {
        std::string s = "foobar";
        PyObject* o = parse_object(s);
        EXPECT_TRUE(PyUnicode_Check(o));
        EXPECT_STREQ("foobar", PyBytes_AsString(PyUnicode_AsASCIIString(o)));
    }
    {
        PyObject* o = parse_object("foobar");
        EXPECT_TRUE(PyUnicode_Check(o));
        EXPECT_STREQ("foobar", PyBytes_AsString(PyUnicode_AsASCIIString(o)));
    }
}

TEST(parse, sequences) {
    {
        std::vector<int> v{1, 2, 3, 4, 5};
        PyObject* o = parse_object(v);
        EXPECT_TRUE(PySequence_Check(o));
        EXPECT_EQ(5, PySequence_Length(o));
        for (ssize_t i = 0; i < PySequence_Length(o); ++i) {
            EXPECT_EQ(i + 1, 
                PyNumber_AsSsize_t(PySequence_GetItem(o, i), nullptr));
        }
    }
    {
        std::deque<int> v{1, 2, 3, 4, 5};
        PyObject* o = parse_object(v);
        EXPECT_TRUE(PySequence_Check(o));
        EXPECT_EQ(5, PySequence_Length(o));
        for (ssize_t i = 0; i < PySequence_Length(o); ++i) {
            EXPECT_EQ(i + 1, 
                PyNumber_AsSsize_t(PySequence_GetItem(o, i), nullptr));
        }
    }
    {
        std::set<int> v{1, 2, 3, 4, 5};
        PyObject* o = parse_object(v);
        EXPECT_TRUE(PySequence_Check(o));
        EXPECT_EQ(5, PySequence_Length(o));
        for (ssize_t i = 0; i < PySequence_Length(o); ++i) {
            EXPECT_EQ(i + 1, 
                PyNumber_AsSsize_t(PySequence_GetItem(o, i), nullptr));
        }
    }
}

TEST(parse, maps) {
    {
        std::map<std::string, int> m{ {"foo", 1}, {"bar", 2} };
        PyObject* o = parse_object(m);
        EXPECT_TRUE(PyDict_Check(o));
        EXPECT_EQ(1, PyNumber_AsSsize_t(PyDict_GetItem(o, parse_object("foo")),
                                        nullptr));
        EXPECT_EQ(2, PyNumber_AsSsize_t(PyDict_GetItem(o, parse_object("bar")),
                                        nullptr));
    }
    {
        std::multimap<std::string, int> m{ {"foo", 1}, {"bar", 2} };
        PyObject* o = parse_object(m);
        EXPECT_TRUE(PyDict_Check(o));
        EXPECT_EQ(1, PyNumber_AsSsize_t(PyDict_GetItem(o, parse_object("foo")),
                                        nullptr));
        EXPECT_EQ(2, PyNumber_AsSsize_t(PyDict_GetItem(o, parse_object("bar")),
                                        nullptr));
    }
}

TEST(parse, tuples) {
    {
        std::tuple<int, int, std::string> t{1, 2, "foobar"};
        PyObject* o = parse_object(t);
        EXPECT_TRUE(PyTuple_Check(o));
        EXPECT_EQ(1, PyNumber_AsSsize_t(PyTuple_GetItem(o, 0),
                                        nullptr));
        EXPECT_EQ(2, PyNumber_AsSsize_t(PyTuple_GetItem(o, 1),
                                        nullptr));
        EXPECT_EQ(std::string("foobar"), 
            PyBytes_AsString(PyUnicode_AsASCIIString(PyTuple_GetItem(o, 2))));
    }

    {
        PyObject* o = parse_object(std::make_tuple<int, int, std::string>
                (1, 2, "foobar"));
        EXPECT_TRUE(PyTuple_Check(o));
        EXPECT_EQ(1, PyNumber_AsSsize_t(PyTuple_GetItem(o, 0),
                                        nullptr));
        EXPECT_EQ(2, PyNumber_AsSsize_t(PyTuple_GetItem(o, 1),
                                        nullptr));
        EXPECT_EQ(std::string("foobar"), 
            PyBytes_AsString(PyUnicode_AsASCIIString(PyTuple_GetItem(o, 2))));
    }
}

TEST(parse, multi) {
    {
        PyObject* o = parse_object(1, 2, 3);
        EXPECT_TRUE(PySequence_Check(o));
        EXPECT_EQ(3, PySequence_Length(o));
        for (ssize_t i = 0; i < PySequence_Length(o); ++i) {
            EXPECT_EQ(i + 1, 
                PyNumber_AsSsize_t(PySequence_GetItem(o, i), nullptr));
        }
    }
    {
        PyObject* o = parse_object(1, std::vector<int>{2, 3, 4}, 
                                      std::map<int, int>{ {5, 6}, {7, 8} });
        EXPECT_TRUE(PySequence_Check(o));
        EXPECT_EQ(3, PySequence_Length(o));

        EXPECT_TRUE(PyNumber_Check(PySequence_GetItem(o, 0)));
        EXPECT_TRUE(PySequence_Check(PySequence_GetItem(o, 1)));
        EXPECT_TRUE(PyDict_Check(PySequence_GetItem(o, 2)));
    }
}

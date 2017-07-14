#include <pie/parse.h>
#include <pie/object.h>

#include <gtest/gtest.h>

using pie::object;
using pie::parse_object;

TEST(object, default_constructor) {
    object o;
    EXPECT_EQ(nullptr, o.get());
}

TEST(object, pyobject_constructor) {
    PyObject* po = parse_object(42);
    object o(po);
    EXPECT_EQ(po, o.get());
}

TEST(object, parse_constructor) {
    object o(10);
    EXPECT_TRUE(PyNumber_Check(o.get()));
}

TEST(object, copy_contructor) {
    object o(10);
    ssize_t refcount = o->ob_refcnt;
    object copy(o);
    EXPECT_EQ(refcount + 1, o->ob_refcnt);
    EXPECT_EQ(refcount + 1, copy->ob_refcnt);
}

TEST(object, move_contructor) {
    object o(10);
    ssize_t refcount = o->ob_refcnt;
    object move(std::move(o));
    EXPECT_EQ(nullptr, o.get());
    EXPECT_EQ(refcount, move->ob_refcnt);
}

TEST(object, parse_assignment) {
    object o = 10;
    EXPECT_TRUE(PyNumber_Check(o.get()));
}

TEST(object, copy_assignment) {
    object o(10);
    ssize_t refcount = o->ob_refcnt;
    object copy = o;
    EXPECT_EQ(refcount + 1, o->ob_refcnt);
    EXPECT_EQ(refcount + 1, copy->ob_refcnt);
}

TEST(object, move_assignment) {
    object o(10);
    ssize_t refcount = o->ob_refcnt;
    object move = std::move(o);
    EXPECT_EQ(nullptr, o.get());
    EXPECT_EQ(refcount, move->ob_refcnt);
}

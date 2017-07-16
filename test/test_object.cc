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

TEST(object, comparison) {
    object one = 1;
    object two = 2;
    EXPECT_LT(one, two);
    EXPECT_LE(one, two);
    EXPECT_LE(one, one);
    EXPECT_EQ(one, one);
    EXPECT_EQ(two, two);
    EXPECT_NE(one, two);
    EXPECT_NE(two, one);
    EXPECT_GT(two, one);
    EXPECT_GE(two, one);
    EXPECT_GE(one, one);
}

TEST(object, hash) {
    object o1 = 1;
    object o2 = 1;
    EXPECT_EQ(o1.hash(), o2.hash());
}

TEST(object, call) {
    object os_listdir = pie::getattr(PyImport_ImportModule("os"), "listdir");
    EXPECT_TRUE(os_listdir());
    EXPECT_TRUE(os_listdir("/"));
}

TEST(object, sequences) {
    object seq(1, 2, 3, 4, 5);
    EXPECT_EQ(5, seq.length());
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(object(i + 1), seq[i]);
        seq[i] = i;
        EXPECT_EQ(object(i), seq[i]);
    }

    size_t i = 0;
    for (auto o: seq) {
        EXPECT_EQ(object(i), o);
        ++i;
    }
}

TEST(object, numeric_operators) {
    object zero = 0;
    object one = 1;
    object two = 2;
    object three = 3;
    object four = 4;
    {
        object new_one = one;
        EXPECT_EQ(three, one + two);
        EXPECT_EQ(three, new_one += two);
    }
    {
        object new_three = three;
        EXPECT_EQ(one, three - two);
        EXPECT_EQ(one, new_three -= two);
    }
    {
        object new_one = one;
        EXPECT_EQ(two, one * two);
        EXPECT_EQ(two, new_one *= two);
    }
    {
        object new_four = four;
        EXPECT_EQ(two, four / two);
        EXPECT_EQ(two, new_four /= two);
    }
    {
        object new_four = four;
        EXPECT_EQ(zero, four % two);
        EXPECT_EQ(zero, new_four %= two);
    }
    object negative_one = -1;

    EXPECT_EQ(negative_one, -one);
    EXPECT_EQ(one, +one);
    EXPECT_EQ(four, pow(two, two));
    EXPECT_EQ(one, abs(negative_one));
}

TEST(object, bitwise_operators) {
    object zero = 0;
    object one = 1;
    object two = 2;
    object three = 3;
    object four = 4;

    {
        object new_one = one;
        EXPECT_EQ(four, one << two);
        EXPECT_EQ(four, new_one <<= two);
    }
    {
        object new_two = two;
        EXPECT_EQ(one, two >> one);
        EXPECT_EQ(one, new_two >>= one);
    }
    {
        object new_two = two;
        EXPECT_EQ(zero, two & one);
        EXPECT_EQ(zero, new_two &= one);
    }
    {
        object new_three = three;
        EXPECT_EQ(two, three ^ one);
        EXPECT_EQ(two, new_three ^= one);
    }
    {
        object new_two = two;
        EXPECT_EQ(three, two | one);
        EXPECT_EQ(three, new_two |= one);
    }
    EXPECT_EQ(-four, ~three);
}

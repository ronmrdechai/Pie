#include <pie/object.h>
#include <pie/error.h>

#include <gtest/gtest.h>

using pie::object;
using pie::error;

TEST(error, division_by_zero) {
    object zero = 0;
    object one = 1;
    EXPECT_THROW(one / zero, error);
}

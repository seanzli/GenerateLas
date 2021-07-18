#include <iostream>

#include <gtest/gtest.h>

#include "StructDef.h"

TEST(PointStructTest, HandlerBasic) {
    Point<double> a(1.1, 2.2, 3.3);
    Point<double> b(1.1, 2.2, 3.3);
    Point<double> c(2.2, 4.4, 6.6);

    ASSERT_EQ(a + b, c) << "Add";
    ASSERT_EQ(c - a, b) << "Sub";
    ASSERT_EQ(a.distance(b), 0.0) << "Point distance";

    ATT att(a);
    ASSERT_EQ(att.roll, att.x) << "ATT test";

    att.x = 2.2;
    ASSERT_EQ(att.roll, att.x) << "ATT test2";
}


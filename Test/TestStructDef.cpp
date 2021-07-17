#include <iostream>

#include <gtest/gtest.h>

#include "StructDef.h"

TEST(PointStructTest, Handle) {
    Point<double> a(1.1, 2.2, 3.3);
    Point<double> b(1.1, 2.2, 3.3);
    Point<double> c(2.2, 4.4, 6.6);

    ATT att(a);

    ASSERT_EQ(a + b, c) << "Add";
    ASSERT_EQ(c - a, b) << "Sub";
    ASSERT_EQ(att.roll, att.x) << "ATT test";

    att.x = 2.2;
    ASSERT_EQ(att.roll, att.x) << "ATT test2";
    

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
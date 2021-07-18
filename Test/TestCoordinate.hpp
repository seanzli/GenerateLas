#include <iostream>
#include <gtest/gtest.h>

#include "Coordinate.hpp"

TEST(CoordinateTest, handleFunction) {
    // EllipBuilder
    Ellip para = EllipBuilder(WGS84);

    ASSERT_EQ(para.major, 6378137.0) << "EllipBuilder.type.major";
    ASSERT_EQ(para.minor, 6356752.31424518) << "EllipBuilder.type.minor";

    para = EllipBuilder(6378137.0, 6356752.31424518);
    ASSERT_EQ(para.major, 6378137.0) << "EllipBuilder.type.major2";
    ASSERT_EQ(para.minor, 6356752.31424518) << "EllipBuilder.type.minor2";

    // coordinate
    Coordinate *p_coord1 = Coordinate::instance(para);
    Coordinate *p_coord2 = Coordinate::instance(para);

    ASSERT_EQ(p_coord1, p_coord2) << "Coordinate singleton test";
}
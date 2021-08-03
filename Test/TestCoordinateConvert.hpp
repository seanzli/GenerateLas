/*
 * @Descripttion: Test coordinate convert
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-08-01 18:05:48
 * @LastEditors: Sean
 * @LastEditTime: 2021-08-03 20:40:32
 */

#include <iostream>
#include <gtest/gtest.h>

#include "CoordinateConvert.hpp"


TEST(CoordinateConvertTest, handleFunction) {
    Coordinate::Ellipsoid ellip{Coordinate::WGS84};
    EXPECT_EQ(ellip.a(), 6378137.0);
    EXPECT_NEAR(ellip.e() * ellip.e(), 0.00669437999013, 1e-10);
}
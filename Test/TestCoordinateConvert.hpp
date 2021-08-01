/*
 * @Descripttion: Test coordinate convert
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-08-01 18:05:48
 * @LastEditors: Sean
 * @LastEditTime: 2021-08-01 18:14:05
 */

#include <iostream>
#include <gtest/gtest.h>

#include "CoordinateConvert.hpp"


TEST(CoordinateConvertTest, handleFunction) {
    Coordinate::Ellipsoid ellip{Coordinate::WGS84};
    EXPECT_EQ(ellip.a(), 6378137.0);
}
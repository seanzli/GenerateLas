/*
 * @Descripttion: 
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-07-25 16:04:21
 * @LastEditors: Sean
 * @LastEditTime: 2021-07-25 16:36:13
 */

#include <gtest/gtest.h>

#include "Parameters.hpp"

TEST(ParametersTest, handlerParameter) {

    Eigen::Matrix<double, 3, 3> rotate_matrix = Eigen::Matrix<double, 3, 3>::Zero();
    rotate_matrix(0, 2) = 1.0;
    rotate_matrix(1, 1) = 1.0;
    rotate_matrix(2, 0) = -1.0;
    Eigen::Matrix<double, 3, 1> trans_arm = Eigen::Matrix<double, 3, 1>::Zero();
    trans_arm(0, 0) = 0.1645;
    trans_arm(1, 0) = 0.0002;
    trans_arm(2, 0) = -0.004;
    Eigen::Matrix<double, 3, 1> angle_check = Eigen::Matrix<double, 3, 1>(0.25569, -0.27103, -0.00771);

    auto tran = GenLas::Parameter(rotate_matrix, trans_arm,angle_check).getTrans();

}
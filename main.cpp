/*
 * @Description: 
 * @Author: Sean
 * @Date: 2021-07-13 21:11:37
 * @LastEditTime: 2021-07-26 21:05:47
 * @LastEditors: Sean
 * @Reference: 
 */
#include <iostream>
#include <glog/logging.h>

#include <string>

#include "GenerateLas.hpp"

int main(int argc, char* argv[]) {
    // google-logging-library initailization
    google::InitGoogleLogging(argv[0]);
    google::SetLogDestination(google::GLOG_INFO, "../log/log_");

    LOG(INFO) << "------start-------\n";
    //
    GenerateLas generate;
    generate.defindCoordinate(EllipBuilder(WGS84));
    
    GenLas::PosFilePath pos_file("/home/z/Documents/data/sbet_Mission.out");
    GenLas::LidarFilePath sdc_file("/home/z/Documents/data/190326_072129_Scanner_1.sdc");

    std::string out_file = "/home/z/Documents/data/190326_072129_Scanner_1.las";
    
    
    Eigen::Matrix<double, 3, 3> rotate_matrix = Eigen::Matrix<double, 3, 3>::Zero();

    rotate_matrix(0, 2) = 1.0;
    rotate_matrix(1, 1) = 1.0;
    rotate_matrix(2, 0) = -1.0;

    Eigen::Matrix<double, 3, 1> trans_arm = Eigen::Matrix<double, 3, 1>::Zero();
    trans_arm(0, 0) = 0.1645;
    trans_arm(1, 0) = 0.0002;
    trans_arm(2, 0) = -0.004;

    Eigen::Matrix<double, 3, 1> angle_check = Eigen::Matrix<double, 3, 1>(0.25569, -0.27103, -0.00771);
    
    GenLas::Parameter::instance().SetLidar2body(rotate_matrix, trans_arm, angle_check);

    if (pos_file.m_valid && sdc_file.m_valid)
        generate.mainProcess(LIDAR_TYPE_RIEGL, sdc_file, pos_file, out_file);
    else
        LOG(ERROR) << "pos file or lidar file, can not open! \n";

    LOG(INFO) << "------terminal-------\n";

    return 0;
}
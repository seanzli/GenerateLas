/*
 * @Description: 
 * @Author: Sean
 * @Date: 2021-07-13 21:11:37
 * @LastEditTime: 2021-07-28 21:30:53
 * @LastEditors: Sean
 * @Reference: 
 */
#include <iostream>
#include <glog/logging.h>
#include <string>
#include <regex>

//3rd
#include "ini.h"

#include "GenerateLas.hpp"

int setPara() {
    // use https://github.com/pulzed/mINI.git
    std::string parameter_file = "parameter.ini";
    mINI::INIFile file(parameter_file);
    mINI::INIStructure ini;
    
    if (file.read(ini) == false) {
        LOG(ERROR) << "parameter.ini read false! \n"; 
        return 0;
    }
    
    std::string matrix = ini["rotate"]["matrix"];
    std::vector<double> data;
    std::regex re(",");
    std::vector<std::string> matrix_s(std::sregex_token_iterator(matrix.begin(), matrix.end(), re, -1),
                                      std::sregex_token_iterator());
    if (matrix_s.size() != 9) {
        LOG(ERROR) << "rotate matrix: decode error!\n";
        return 0;
    }

    Eigen::Matrix<double, 3, 3> rotate_matrix = Eigen::Matrix<double, 3, 3>::Zero();
    for (int i = 0; i < 9; ++i)
        rotate_matrix(i) = std::stod(matrix_s[i]);

    Eigen::Matrix<double, 3, 1> trans_arm = Eigen::Matrix<double, 3, 1>::Zero();
    trans_arm(0, 0) = std::stod(ini["trans"]["x"]);
    trans_arm(1, 0) = std::stod(ini["trans"]["y"]);
    trans_arm(2, 0) = std::stod(ini["trans"]["z"]);

    Eigen::Matrix<double, 3, 1> angle_check = Eigen::Matrix<double, 3, 1>::Zero();
    angle_check(0, 0) = std::stod(ini["check angle"]["roll"]);
    angle_check(1, 0) = std::stod(ini["check angle"]["pitch"]);
    angle_check(2, 0) = std::stod(ini["check angle"]["heading"]);
    
    GenLas::Parameter::instance().SetLidar2body(rotate_matrix, trans_arm, angle_check);
}

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
    
    if (pos_file.m_valid && sdc_file.m_valid)
        generate.mainProcess(LIDAR_TYPE_RIEGL, sdc_file, pos_file, out_file);
    else
        LOG(ERROR) << "pos file or lidar file, can not open! \n";

    LOG(INFO) << "------terminal-------\n";

    return 0;
}
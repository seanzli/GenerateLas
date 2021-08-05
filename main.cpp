/*
 * @Description: 
 * @Author: Sean
 * @Date: 2021-07-13 21:11:37
 * @LastEditTime: 2021-08-05 17:15:48
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



int main(int argc, char* argv[]) {
    // google-logging-library initailization
    google::InitGoogleLogging(argv[0]);
    google::SetLogDestination(google::GLOG_INFO, "../log/log_");

    LOG(INFO) << "------start-------\n";
    // decode device parameter 
    GenLas::setPara(std::string("../parameter.ini"));

    // get data file path
    GenerateLas generate;
    generate.defindCoordinate(Coordinate::Ellipsoid{Coordinate::WGS84}, Coordinate::RectangleCoord{Coordinate::UTM});
    
    GenLas::PosFilePath pos_file("/home/z/Documents/data/sbet_Mission.out");
    GenLas::LidarFilePath sdc_file("/home/z/Documents/data/190326_072129_Scanner_1.sdc");
    std::string out_file = "/home/z/Documents/data/190326_072129_Scanner_1.las";
    
    // calculate
    if (pos_file.m_valid && sdc_file.m_valid)
        generate.mainProcess(LIDAR_TYPE_RIEGL, sdc_file, pos_file, out_file);
    else
        LOG(ERROR) << "pos file or lidar file, can not open! \n";

    LOG(INFO) << "------terminal-------\n";

    return 0;
}
/*
 * @Description: 
 * @Author: Sean
 * @Date: 2021-07-13 21:11:37
 * @LastEditTime: 2021-07-13 21:53:24
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

    LOG(INFO) << "------start-------" << std::endl;
    //
    GenerateLas generate;
    generate.defindCoordinate(EllipBuilder(WGS84));
    
    std::string pos_file = "/home/z/Documents/data/sbet_Mission.out";
    std::string sdc_file = "/home/z/Documents/data/190326_072129_Scanner_1.sdc";
    std::string out_file = "/home/z/Documents/data/190326_072129_Scanner_1.las";
    
    generate.mainProcess(LIDAR_TYPE_RIEGL, sdc_file, pos_file, out_file);

    LOG(INFO) << "------terminal-------" << std::endl;

    return 0;
}
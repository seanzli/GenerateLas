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

#include "GenerateLas.hpp"

int main(int argc, char* argv[]) {
    // google-logging-library initailization
    google::InitGoogleLogging(argv[0]);
    google::SetLogDestination(google::GLOG_INFO, "../log/log_");

    LOG(INFO) << "------start-------" << std::endl;
    //
    GenerateLas generate;
    generate.defindCoordinate(EllipBuilder(WGS84));

    LOG(INFO) << "------terminal-------" << std::endl;

    return 0;
}
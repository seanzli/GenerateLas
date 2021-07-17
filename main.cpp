/*
 * @Description: 
 * @Author: Sean
 * @Date: 2021-07-13 21:11:37
 * @LastEditTime: 2021-07-13 21:53:24
 * @LastEditors: Sean
 * @Reference: 
 */
#include <iostream>

#include <GenerateLas.hpp>

#include <glog/logging.h>

#include "StructDef.h"

int main(int argc, char* argv[]) {
    // google-logging-library initailization
    google::InitGoogleLogging(argv[0]);
    google::SetLogDestination(google::GLOG_INFO, "./log/log_");

    LOG(INFO) << "log - test" << std::endl;

    Point<float> a(1.1,2.2,3.3);
    Point<double> b(1.1,2.2,3.3);

    std::cout << a + b;

    return 0;
}
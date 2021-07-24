/*
 * @Description: Decode LiDAR orignal file
 * @Author: Sean
 * @Date: 2021-07-14 21:52:09
 * @LastEditTime: 2021-07-24 11:08:02
 * @LastEditors: Please set LastEditors
 * @Reference: 
 */
#pragma once

#include <vector>
#include <string>

#include "StructDef.h"

class DecodeLidarFile {
public:
    DecodeLidarFile() {}

    DecodeLidarFile(const DecodeLidarFile&) = delete;
    DecodeLidarFile& operator=(const DecodeLidarFile&) = delete;

    virtual ~DecodeLidarFile() {}
    virtual unsigned int decodeFile(const std::string& lidar_path,
                                    const int& read_num , 
                                    std::vector<LidarPoint<double>>& out) = 0;
};
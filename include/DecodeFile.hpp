/*
 * @Description: Decode LiDAR orignal file
 * @Author: Sean
 * @Date: 2021-07-14 21:52:09
 * @LastEditTime: 2021-07-14 22:02:18
 * @LastEditors: Sean
 * @Reference: 
 */
#pragma once
#include "StructDef.h"

#include <vector>
#include <string>

class DecodeLidarFile {
public:
    DecodeLidarFile() {}

    DecodeLidarFile(const DecodeLidarFile&) = delete;
    DecodeLidarFile& operator=(const DecodeLidarFile&) = delete;

    virtual ~DecodeLidarFile() {}
    virtual unsigned int decodeFile(const std::string& file_path,
                                    const int& read_num , 
                                    std::vector<LidarPoint<double>>& out) = 0;
};
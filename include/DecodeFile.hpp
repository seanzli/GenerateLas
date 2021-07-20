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

class DecodeLidarFile {
public:
    DecodeLidarFile() {}
    virtual ~DecodeLidarFile() {};
    virtual unsigned int decodeFile(const char* p_file,
                                    const int& length, 
                                    const int& read_num , 
                                    std::vector<LidarPoint<double>>& out) {};
};
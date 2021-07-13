/*
 * @Author: your name
 * @Date: 2021-07-13 21:13:43
 * @LastEditTime: 2021-07-13 21:38:29
 * @LastEditors: Sean
 * @Description: In User Settings Edit
 * @FilePath: \GenerateLas\include\GenerateLas.hpp
 */
#include <vector>
#include <string>

#include "StructDef.h"

class GenerateLas {
public:
    GenerateLas() = default;
    ~GenerateLas() = default;

    void mainProcess(const std::string& lidar_file, const std::string& output_file);
};

class DecodeLidarFile {
public:
    DecodeLidarFile() = default;
    virtual ~DecodeLidarFile() {};
    virtual void decodeFile(const char* p_file, const int& length, std::vector<LidarPoint<double>>& out);
};

class DecodeSdcLidarFile : public DecodeLidarFile {

};
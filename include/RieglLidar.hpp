/*
 * @Description: Decode Riegl Lidar File
 * @Author: Sean
 * @Date: 2021-07-14 21:54:07
 * @LastEditTime: 2021-07-25 10:13:34
 * @LastEditors: Sean
 * @Reference: 
 */

#pragma once

#include "DecodeFile.hpp"

#include <cstring>
#include <cstdio>
#include <glog/logging.h>

class DecodeSdcLidarFile : public DecodeLidarFile {
public:
    DecodeSdcLidarFile() : fp(nullptr), p_data(nullptr) {}

    virtual ~DecodeSdcLidarFile() override {
        if (fp)
            fclose(fp);
        if (p_data) {
            delete p_data;
            p_data = nullptr;
        }
    }
    virtual unsigned int decodeFile(const std::string & file_path, const int& read_num ,
                            std::vector<LidarPoint<double>>& out) override {
        if (nullptr == fp && openLidarFile(file_path) == false)
            return 0;
        if (p_data == nullptr)
            applyBuffer(read_num);
        
        int num = fread(p_data, m_struct_size, read_num, fp);
        for (int i = 0; i < num; i++)
            out.emplace_back(convertSdc2LidarPoint(p_data[i]));
        return num;
    }

private:
#pragma pack(1)
    struct SdcStruct
    {
        double gps_time;
		float range;
		float theta;
		float x;
		float y;
		float z;
		unsigned short amplitude;
		unsigned short width;
		unsigned char targettype;
		unsigned char target;
		unsigned char numtarget;
		unsigned short rgubdex;
		unsigned char channeldesc;
		unsigned char classid;
		float rho;
		signed short reflectance;
    };
#pragma pack()
    const int m_struct_size = sizeof(SdcStruct);
    LidarPoint<double> convertSdc2LidarPoint(const SdcStruct& in) const{
        LidarPoint<double> out;
        out.point.x = in.x;
        out.point.y = in.y;
        out.point.z = in.z;
        out.gps_time = in.gps_time;
        out.numbersOfReturns = in.numtarget;
        out.returnNumber = in.target;
        out.ref = in.reflectance;
        return out;
    }

    void decodeHead(FILE* _fp) {
        unsigned long long sdc_header_size = 0;
        fread(&sdc_header_size, sizeof(char)*4, 1, _fp);
        fseek(_fp, sdc_header_size, 0);
    }

    FILE *fp;
    SdcStruct* p_data;
    unsigned long long m_point_max;

    bool openLidarFile(const std::string& file_path) {
        VLOG(3) << "Open lidar file = " << file_path << "\n";
        fp = fopen(file_path.c_str(), "rb");
        if (fp == nullptr) {
            LOG(ERROR) << "LIDAR decode file open fault!\n";
            return false;
        }
        decodeHead(fp);
        return true;
    }

    void applyBuffer(const int& num) {
        VLOG(3) << "Apply decode lidar buffer size = "
                << num << " * " << m_struct_size 
                << " = " << num * m_struct_size
                << "\n";
        try {
            p_data = new SdcStruct[num];
        } catch (std::exception& e) {
            LOG(ERROR) << "LIDAR decode buffer apply fault!\n";
            std::cerr << e.what() << std::endl;
        }
    }

};
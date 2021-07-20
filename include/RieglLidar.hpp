/*
 * @Description: Decode Riegl Lidar File
 * @Author: Sean
 * @Date: 2021-07-14 21:54:07
 * @LastEditTime: 2021-07-16 23:19:01
 * @LastEditors: Sean
 * @Reference: 
 */

#pragma once

#include "DecodeFile.hpp"

#include <cstring>
#include <cstdio>

class DecodeSdcLidarFile : public DecodeLidarFile {
public:
    DecodeSdcLidarFile() {}
    virtual ~DecodeSdcLidarFile() override {}
    virtual unsigned int decodeFile(const char* p_file, const int& length, const int& read_num ,
                            std::vector<LidarPoint<double>>& out) override {
        const int size = std::min(read_num * m_struct_size, length) / m_struct_size;
        SdcStruct *arr = new SdcStruct[size];
        memcpy(arr, p_file, size*m_struct_size);
        p_file +=  size*m_struct_size;
        for (int i = 0; i < size; ++i)
            out.emplace_back(convertSdc2LidarPoint(arr[i]));
        return size;
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
};
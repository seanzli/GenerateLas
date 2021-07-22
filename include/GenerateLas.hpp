/*
 * @Author: Sean
 * @Date: 2021-07-13 21:13:43
 * @LastEditTime: 2021-07-16 22:46:17
 * @LastEditors: Sean
 * @Description: Generate Las Function Main Process
 * @FilePath: \GenerateLas\include\GenerateLas.hpp
 */
#include <vector>
#include <string>
#include <cstdio>
#include <memory>
#include <limits>

#include "StructDef.h"
#include "DecodeFileFactory.hpp"
#include "DecodeSbet.hpp"
#include "Coordinate.hpp"

class GenerateLas {
public:
    GenerateLas() = default;
    ~GenerateLas() = default;

    // define coordinate, class coordinate is singleton mono pattern, use as globle, 
    // use instance() to get
    // use instance(const double&, const double&) to modify;
    void defindCoordinate(Ellip para) {
        Coordinate::instance(para);
    }

    /**
     * @description: main process of generate las
     * @param  {Lidar_type}  type:          lidar type
     * @param  {std::string} lidar_file:    lidar file path, include file name
     * @param  {std::string} pos_file:      pos file path, include file name, should be .out file
     * @param  {std::string} output_file:   output file path, include file name, should be .las file
     * @return {int}         0 = normal, 
     *                      -1 = pos decode error
     *                      -2 = lidar type error
     *                      -3 = lidar open error
     */
    int mainProcess(const Lidar_type& type, 
                     const std::string& lidar_file,
                     const std::string& pos_file,
                     const std::string& output_file) {
        // decode pos file
        std::vector<Traj> traj;
        getPos(pos_file, traj);
        if (traj.size() == 0) {
            LOG(ERROR) <<"pos file decode error!";
            return -1;
        }

        // check lidar file
        DecodeLidarFile *p_decoder = DecodeFileFactory::instance(type);
        if (p_decoder == nullptr) {
            LOG(ERROR) << "lidar type error!";
            return -2;
        }

        FILE *fp = fopen(lidar_file.c_str(), "rb");
        if (fp == nullptr) {
            LOG(ERROR) << "lidar file can not open!";
            return -3;
        }
        fclose(fp);

        int read_num = 1024;
        
        std::vector<LidarPoint<double>> point;
        while (fp) {
            // decode lidar point
            int num = p_decoder->decodeFile(lidar_file, m_read_point_num, point);
            // decode las point
        }

        return 0;
    }

private:
    unsigned int m_read_point_num = 1024 * 20;

    void getPos(const std::string& pos_file, std::vector<Traj>& out) {
        DecodePosFile* p_decoder = new DecodeSbetFile();
        p_decoder->decodePos(pos_file, out);
    }
};




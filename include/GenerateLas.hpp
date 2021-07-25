/*
 * @Author: Sean
 * @Date: 2021-07-13 21:13:43
 * @LastEditTime: 2021-07-25 10:13:47
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
#include "GenFileString.hpp"
#include "DecodeFileFactory.hpp"
#include "DecodeSbet.hpp"
#include "Coordinate.hpp"

class GenerateLas {
public:
    GenerateLas() : m_read_point_num(1024 * 20) {}
    GenerateLas(unsigned int _size) : m_read_point_num(_size) {}
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
                     const GenLas::LidarFilePath& lidar_file,
                     const GenLas::PosFilePath& pos_file,
                     const std::string& output_file) {
        // decode pos file
        //DLOG() << "Decode Pos File------\n";
        std::vector<Traj> traj;
        getPos(pos_file, traj);
        checkTraj(traj);

        // check lidar file
        //DLOG() << "Decode Lidar File------\n";
        std::shared_ptr<DecodeLidarFile> p_decoder = DecodeFileFactory::instance(type);
        checkLidarFile(p_decoder, lidar_file);

        // calculate
        //VLOG(0) << "Calculate Point------\n";
        int read_num = m_read_point_num;
        std::vector<LidarPoint<double>> point;
        while (read_num) {
            // decode lidar point
            point.clear();
            read_num = p_decoder->decodeFile(lidar_file, m_read_point_num, point);
            //VLOG(5) << "--> Decode point num = " << read_num << "\n";
            // decode las point
        }
        return 0;
    }

private:
    unsigned int m_read_point_num;

    void getPos(const std::string& pos_file, std::vector<Traj>& out) {
        std::shared_ptr<DecodePosFile> p_decoder(new DecodeSbetFile());
        p_decoder->decodePos(pos_file, out);
    }

    int checkLidarFile(std::shared_ptr<DecodeLidarFile> p_decoder, const std::string& lidar_file) {
        if (p_decoder == nullptr) {
            LOG(ERROR) << "lidar type error!\n";
            throw -2;
            return -2;
        }
        FILE *fp = fopen(lidar_file.c_str(), "rb");
        if (fp == nullptr) {
            LOG(ERROR) << "lidar file can not open!\n";
            throw -3;
            return -3;
        }
        fclose(fp);
        fp = nullptr;
        return 0;
    }
    int checkTraj(const std::vector<Traj>& traj) {
        VLOG(3) << "traj size = " << traj.size() << "\n";
        if (traj.size() == 0) {
            LOG(ERROR) <<"pos file decode error!\n";
            throw -1;
            return -1;
        }
        return 0;
    }
};




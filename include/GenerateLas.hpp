/*
 * @Author: Sean
 * @Date: 2021-07-13 21:13:43
 * @LastEditTime: 2021-07-29 20:42:52
 * @LastEditors: Sean
 * @Description: Generate Las Function Main Process
 * @FilePath: \GenerateLas\include\GenerateLas.hpp
 */

// c++
#include <vector>
#include <string>
#include <cstdio>
#include <memory>
#include <limits>

// omp
#include <omp.h>

// method from other header files
#include "StructDef.h"
#include "GenFileString.hpp"
#include "DecodeFileFactory.hpp"
#include "DecodeSbet.hpp"
#include "Coordinate.hpp"
#include "Buffer.hpp"

#include "Parameters.hpp"

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
        VLOG(0) << "Decode Pos File------\n";
        std::vector<Traj> traj;
        getPos(pos_file, traj);
        checkTraj(traj);

        // check lidar file
        VLOG(0) << "Decode Lidar File------\n";
        std::shared_ptr<DecodeLidarFile> p_decoder = DecodeFileFactory::instance(type);
        checkLidarFile(p_decoder, lidar_file);

        // calculate
        VLOG(0) << "Calculate Point------\n";
        int read_num = m_read_point_num;
        std::vector<LidarPoint<double>> point;
        Buffer<Point<double>> out;
        while (read_num) {
            // decode lidar point
            point.clear();
            read_num = p_decoder->decodeFile(lidar_file, m_read_point_num, point);
            VLOG(5) << "--> Decode point num = " << read_num << "\n";
            // decode las point
            calculate(point, traj, out);
        }
        return 0;
    }

private:
    unsigned int m_read_point_num;
    double m_precision = 1e-9;

    void getPos(const std::string& pos_file, std::vector<Traj>& out) {
        VLOG(3) << "Decode pos file -------\n";
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
    size_t calculate(const std::vector<LidarPoint<double>>& point, 
                       const std::vector<Traj>& traj,
                       Buffer<Point<double>>& out) {
        if (point.size() == 0)
            return 0;
        std::vector<Point<double>> _out(point.size());
//#pragma omp parallel for
        for (int i = 0; i < point.size(); ++i) {
            Traj cur_traj = getTrajPoint(point[i].gps_time, traj);
            calculate(cur_traj, point[i], _out[i]);
        }
        out.push_back(_out);
        return point.size();
    }
    
    Traj getTrajPoint(const double gps_time, const std::vector<Traj>& traj_list) {
        int left = 0, right = traj_list.size() - 1;
        int mid = 0;
        double dif = 0.0;

        // binary search
        while (left + 1 < right) {
            mid = left + (right - left) / 2;
            dif = diffSec(traj_list[mid].gps_time, gps_time);
            if (std::abs(dif) < m_precision)
                return traj_list[mid];
            else if (dif < 0) // mid < gps time
                left = mid;
            else
                right = mid;
        }

        // output
        if (left == right)
            return traj_list[left];
        return interpolationTraj(gps_time, traj_list[left], traj_list[right]);
    }

    Traj interpolationTraj(double gps_time, const Traj& left, const Traj& right) {
        Traj out = left;
        out.gps_time = gps_time;
        double ratio = diffSec(gps_time , left.gps_time) / diffSec(right.gps_time , left.gps_time);
        
        out.pos = (right.pos - left.pos) * ratio + left.pos;
        out.att = (right.att - left.att) * ratio + left.att;
        out.val = (right.val - left.val) * ratio + left.val;
        return out;
    }

    void calculate(const Traj& traj,const LidarPoint<double>& point, Point<double>& out) {
        Eigen::Matrix<double, 3, 1> _point(point.point.x, point.point.y, point.point.z);

        auto _p = GenLas::Parameter::instance().getTrans();

        _point = _p * _point;

        out.x = _point(0,0) + traj.pos.x;
        out.y = _point(1,0) + traj.pos.y;
        out.z = _point(2,0) + traj.pos.z;

        return;
    }

    double diffSec(double sec1, double sec2) {
        sec1 = sec1 - (unsigned)(sec1) / SECENDS_IN_DAY * SECENDS_IN_DAY;
        sec2 = sec2 - (unsigned)(sec2) / SECENDS_IN_DAY * SECENDS_IN_DAY;
        return sec1 - sec2;
    }
};




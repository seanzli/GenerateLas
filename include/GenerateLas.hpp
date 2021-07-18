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
     * @return {*}
     */
    void mainProcess(const Lidar_type& type, 
                     const std::string& lidar_file,
                     const std::string& pos_file,
                     const std::string& output_file) {

        DecodeLidarFile *p_decoder = DecodeFileFactory::instance(type);
        if (p_decoder == nullptr)   return;

        FILE *fp = fopen(lidar_file.c_str(), "rb");
        if (fp == nullptr)
            return;
        
        std::vector<Traj> traj;
        getPos(pos_file, traj);

        auto buffer = applyBuffer();
        
        std::vector<LidarPoint<double>> point;
        int num = 0;
        while (fp) {
            fread(buffer, sizeof(char), m_buffer_length, fp);
            num = p_decoder->decodeFile(buffer, m_buffer_length, num, point);

            // decode point
        }

        delete buffer;
    }

private:
    unsigned long long m_buffer_length = 1024 * 20;

    /**
     * @description: apply a new buffer, need to delete outside;
     * @param  {*}
     * @return {*}  char*
     */
    char* applyBuffer() {
        try {
            return new char[m_buffer_length];
        }
        catch(const std::exception& e) {
            std::cerr << "buffer allocator error, no more memory." << std::endl;
            std::cerr << e.what() << '\n';
        }
        return nullptr;
    }

    void getPos(const std::string& pos_file, std::vector<Traj>& out) {
        DecodePosFile* p_decoder = new DecodeSbetFile();
        p_decoder->decodePos(pos_file, out);
    }
};




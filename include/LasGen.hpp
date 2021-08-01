/*
 * @Descripttion: 
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-08-01 09:18:04
 * @LastEditors: Sean
 * @LastEditTime: 2021-08-01 10:23:58
 */

// c++ stl
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

// 3rd
//#include <liblas/liblas.hpp>
//#include "laswriter.hpp"
#include "LAStools/LASlib/inc/laswriter.hpp"

// other
#include "StructDef.h"

namespace GenLas{
    class LasGen{
    public:
        static LasGen& instance() {
            static LasGen m_instamce;
            return m_instamce;
        }

        void setPara(const std::string file_path, const Point<double>& offset) {
            laswriteopener.set_file_name(file_path.c_str());
            lasheader.x_scale_factor = 0.01;
            lasheader.y_scale_factor = 0.01;
            lasheader.z_scale_factor = 0.01;

            lasheader.x_offset = std::round(offset.x);
            lasheader.y_offset = std::round(offset.y);
            lasheader.z_offset = std::round(offset.z);

            lasheader.point_data_format = 1;
            lasheader.point_data_record_length = 28;

            laspoint.init(&lasheader, lasheader.point_data_format, lasheader.point_data_record_length, 0);

            laswriter = laswriteopener.open(&lasheader);
        }   

        ~LasGen() {
            if (laswriter) {
                laswriter->update_inventory(&laspoint);
                laswriter->update_header(&lasheader, TRUE);
                laswriter->close();
                delete laswriter;
            }
            laswriter = nullptr;
        }

        size_t setPoint(std::vector<Point<double>>& point) {
            for (auto itr : point) {
                laspoint.set_X(itr.x);
                laspoint.set_Y(itr.y);
                laspoint.set_Z(itr.z);
                laswriter->write_point(&laspoint);
            }
            laswriter->update_header(&lasheader, TRUE);
        }
        
    private:
        LASwriteOpener laswriteopener;
        LASheader lasheader;
        LASpoint laspoint;
        LASwriter* laswriter = nullptr;
        
        LasGen() {}

    };

};
/*
 * @Author: sean
 * @Date: 2021-07-24 10:30:27
 * @LastEditTime: 2021-07-24 11:07:08
 * @LastEditors: Please set LastEditors
 * @Description: basic tools
 * @FilePath: /GenerateLas/include/Tools.hpp
 */
#pragma once

#include <vector>
#include <string>
#include <cstdio>

#include <glog/logging.h>

namespace GenLas {
    class GenString {
    public:
        std::string m_file_path;
        bool m_valid;
        virtual ~GenString() {}
        bool check(const std::string& _file) {
            FILE *fp = fopen(_file.c_str(), "rd");
            if (fp == nullptr)
                return false;
            fclose(fp);
            return true;
        }
        operator std::string() const{
            return m_file_path;
        }
    };

    class LidarFilePath : public GenString{
    public:
        explicit LidarFilePath(const std::string& _file) {
            m_file_path = _file;
            m_valid = check(_file);
        }
    };

    class PosFilePath : public GenString{
    public:
        explicit PosFilePath(const std::string& _file) {
            m_file_path = _file;
            m_valid = check(_file);
        }
    };

};

class Tools {
    
};
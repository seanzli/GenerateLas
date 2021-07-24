/*
 * @Author: Sean
 * @Date: 2021-07-24 10:30:27
 * @LastEditTime: 2021-07-24 11:25:56
 * @LastEditors: Sean
 * @Description: basic tools
 * @FilePath: /GenerateLas/include/GenFileString.hpp
 */
#pragma once

#include <vector>
#include <string>
#include <cstdio>

#include <glog/logging.h>


/**
 * @description: GanLasString Class, base on std::string, use class name to avoid input mistake;
 * @param  {std::string} m_file_path:   file_path
 * @param  {std::string} m_valid:       check file is exist or not
 */
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
            m_valid = false;
            m_valid = check(_file);
        }
    };

    class PosFilePath : public GenString{
    public:
        explicit PosFilePath(const std::string& _file) {
            m_file_path = _file;
            m_valid = false;
            m_valid = check(_file);
        }
    };
};
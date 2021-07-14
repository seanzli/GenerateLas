/*
 * @Author: Sean
 * @Date: 2021-07-13 21:13:43
 * @LastEditTime: 2021-07-14 21:53:31
 * @LastEditors: Sean
 * @Description: Generate Las Function Main Process
 * @FilePath: \GenerateLas\include\GenerateLas.hpp
 */
#include <vector>
#include <string>

#include "StructDef.h"
#include "DecodeFile.hpp"

class GenerateLas {
public:
    GenerateLas() = default;
    ~GenerateLas() = default;

    void mainProcess(const std::string& lidar_file, const std::string& output_file);
};




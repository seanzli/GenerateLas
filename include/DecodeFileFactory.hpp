/*
 * @Description: factory for decode file function
 * @Author: Sean
 * @Date: 2021-07-15 20:38:15
 * @LastEditTime: 2021-07-25 10:13:57
 * @LastEditors: Sean
 * @Reference: 
 */

#include <glog/logging.h>

#include "RieglLidar.hpp"

enum Lidar_type {
    LIDAR_TYPE_RIEGL
};

class DecodeFileFactory {
public:
    DecodeFileFactory() = default;
    ~DecodeFileFactory() = default;

    static std::shared_ptr<DecodeLidarFile> instance(const Lidar_type & type) {
        switch (type) {
            case LIDAR_TYPE_RIEGL: 
                VLOG(3) << "Lidar File type = riegl\n";
                return std::shared_ptr<DecodeLidarFile>(new DecodeSdcLidarFile()); break;
        }
        return nullptr;
    }

};
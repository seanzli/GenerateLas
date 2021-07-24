/*
 * @Description: factory for decode file function
 * @Author: Sean
 * @Date: 2021-07-15 20:38:15
 * @LastEditTime: 2021-07-15 21:08:36
 * @LastEditors: Sean
 * @Reference: 
 */

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
            case LIDAR_TYPE_RIEGL: return std::shared_ptr<DecodeLidarFile>(new DecodeSdcLidarFile()); break;
        }
        return nullptr;
    }

};
/*
 * @Description: coordinate convert
 * @Author: Sean
 * @Date: 2021-07-15 21:25:53
 * @LastEditTime: 2021-07-16 23:12:54
 * @LastEditors: Sean
 * @Reference: 
 */

#pragma once

#include <cmath>
#include <mutex>

#include "StructDef.h"


// generate ellip arguments
// could use EllipBuilder to instance class Ellip
struct Ellip {
    double major;
    double minor;

    Ellip& operator=(const Ellip& in) {
        this->major = in.major;
        this->minor = in.minor;
        return (*this);
    }
};

enum EllipType{
    WGS84,
};

class EllipBuilder : public Ellip {
public:
    EllipBuilder() = delete;
    EllipBuilder(const EllipType& type) {
        switch (type) {
        case WGS84: para.major = 6378137.0; para.minor = 6356752.31424518; break;
        }
    }
    operator Ellip() {
        return std::move(para);
    }
private:
    Ellip para;
};

// mono
class Coordinate {
public:
    ~Coordinate() = default;

    static Coordinate& instance(const Ellip& para) {
        static Coordinate m_instance = Coordinate(para);
        return m_instance;
    }

    ECEF lla2ecef(const LLA & in) const {
        double n;
        ECEF out;

        n = (m_ellip_para.major*m_ellip_para.major) / sqrt(
            m_ellip_para.major*m_ellip_para.major*cos(in.lat)*cos(in.lat) +
            m_ellip_para.minor * m_ellip_para.minor*sin(in.lat)*sin(in.lat));

        out.x = (n + in.alt)*cos(in.lat)*cos(in.lon);
        out.y = (n + in.alt)*cos(in.lat)*sin(in.lon);
        out.z = ((m_ellip_para.minor*m_ellip_para.minor) / (m_ellip_para.major*m_ellip_para.major)*n
            + in.alt) * sin(in.lat);

        return out;
    }

private:
    Ellip m_ellip_para = EllipBuilder(WGS84);

    Coordinate() = delete;

    Coordinate(const Ellip& para) {
        m_ellip_para = para;
    }
};
/*
 * @Description: coordinate convert
 * @Author: Sean
 * @Date: 2021-07-15 21:25:53
 * @LastEditTime: 2021-07-15 21:53:40
 * @LastEditors: Sean
 * @Reference: 
 */

#pragma once

#include <cmath>

#include "StructDef.h"

class Coordinate {
public:
    Coordinate() = delete;
    ~Coordinate() = default;

    // not thread safe
    static Coordinate& instace() {
        static Coordinate m_instance;
        return m_instance;
    }

    ECEF lla2ecef(const LLA & in) const {
        double n;
        ECEF out;

        n = (m_semimajor_axis*m_semimajor_axis) / sqrt(
            m_semimajor_axis*m_semimajor_axis*cos(in.lat)*cos(in.lat) +
            m_semiminor_axis * m_semiminor_axis*sin(in.lat)*sin(in.lat));

        out.x = (n + in.alt)*cos(in.lat)*cos(in.lon);
        out.y = (n + in.alt)*cos(in.lat)*sin(in.lon);
        out.z = ((m_semiminor_axis*m_semiminor_axis) / (m_semimajor_axis*m_semimajor_axis)*n
            + in.alt) * sin(in.lat);

        return out;
    }

private:
    const double m_semimajor_axis = 6378137.0;
    const double m_semiminor_axis = 6356752.31424518;

    static Coordinate m_instance;
    Coordinate() : m_semimajor_axis(6378137.0), m_semiminor_axis(6356752.31424518) {}

};
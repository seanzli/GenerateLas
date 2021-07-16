/*
 * @Description: coordinate convert
 * @Author: Sean
 * @Date: 2021-07-15 21:25:53
 * @LastEditTime: 2021-07-16 22:34:14
 * @LastEditors: Sean
 * @Reference: 
 */

#pragma once

#include <cmath>
#include <mutex>

#include "StructDef.h"

// mono
class Coordinate {
public:
    ~Coordinate() = default;

    static Coordinate* instance(const double& _major, const double & _minor) {
        m_instance = new Coordinate(_major, _minor);
        return m_instance;
    }

    // do not use this, unless u has define m_instance.
    static Coordinate* instance() {
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
    static double m_semimajor_axis;
    static double m_semiminor_axis;
    static Coordinate *m_instance;

    Coordinate() {
        m_semimajor_axis = 6378137.0;
        m_semiminor_axis = 6356752.31424518;
    }

    Coordinate(const double& _major, const double & _minor) {
        m_semimajor_axis = _major;
        m_semiminor_axis = _minor;
    }
};
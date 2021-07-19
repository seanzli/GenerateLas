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

struct EllipBuilder : public Ellip {
public:
    EllipBuilder() = delete;
    EllipBuilder(const EllipType& type) {
        switch (type) {
        case WGS84: this->major = 6378137.0; this->minor = 6356752.31424518; break;
        }
    }
    EllipBuilder(const double& _major, const double& _minor) {
        this->major = _major;
        this->minor = _minor;
    }
};

// mono
class Coordinate {
public:
    ~Coordinate() = default;

    static Coordinate* instance(const Ellip& para) {
        static Coordinate m_instance = Coordinate(para);
        return &m_instance;
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
    LLA ecef2lla(const ECEF& in) const {
        double p = 0.0, slat = 0.0, N = 0.0, htold = 0.0, latold = 0.0;
    	const double e = 0.00669437999013;	//gps

	    int  i = 0;
	    double tmp = 0.0;

        LLA out;
	    //Check postion valiable
	    tmp = in.distance(ECEF(0.0, 0.0, 0.0));
	    if (fabs(tmp) < m_ellip_para.major*0.5)
		    return out;

	    //Check range
	    p = sqrt(in.x * in.x + in.y* in.y);
	    if (p < 1)
		    return out;

        out.lat = atan2(in.z, p*(1.0 - e));
        out.alt = 0;

        for (i = 0; i < 5; i++)
        {
            slat = sin(out.lat);
            N = m_ellip_para.major / sqrt(1.0 - e * slat*slat);
            htold = out.alt;
            out.alt = p / cos(out.lat) - N;

            latold = out.lat;
            out.lat = atan2(in.z, p*(1.0 - e * (N / (N + out.alt))));
            if (fabs(out.lat - latold) < 1.0e-9 &&
                fabs(out.alt - htold) < (1.0e-9 * m_ellip_para.major))
                break;
        }

        out.lon = atan2(in.y, in.x);
        return out;
    }

private:
    Ellip m_ellip_para = EllipBuilder(WGS84);

    Coordinate() = delete;

    Coordinate(const Ellip& para) {
        m_ellip_para = para;
    }
};
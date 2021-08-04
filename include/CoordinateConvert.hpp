/*
 * @Descripttion:   Coordinate convert namespace 
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-08-01 17:22:21
 * @LastEditors: Sean
 * @LastEditTime: 2021-08-04 22:02:09
 */

// c++ stl
#include <iostream>
#include <cmath>

// 3rd
#include <glog/logging.h>

// struct def
#include "StructDef.h"

#include "Mercartor.hpp"

namespace Coordinate {
    // ellipsoid arguments setting
    enum EllipsoidType{
        WGS84,
    };

    class Ellipsoid {
    public:
        Ellipsoid() {}
        Ellipsoid(const EllipsoidType type) {
            switch (type) {
            case WGS84: this->axis_a = 6378137.0; this->axis_b = 6356752.31424518; break;
            }
            calculate_e();
        }
        Ellipsoid(double _major, double _minor) : axis_a(_major), axis_b(_minor) {
            calculate_e();
        }
        ~Ellipsoid() = default;

        double a()  const noexcept {return this->axis_a;}
        double b()  const noexcept {return this->axis_b;}
        double e()  const noexcept {return this->ellip_e;}
    private:
        double axis_a, axis_b, ellip_e;
        double calculate_e() {
            ellip_e = std::sqrt(a() * a() - b() * b()) / a();
            return ellip_e;
        }
        
    };

    // rectanglar coordinate arguments setting
    enum RectangleType {
        UTM,
    };

    class RectangleCoord {
    public:
        RectangleCoord() {}
        RectangleCoord(const RectangleType type) {
            switch (type) {
                case UTM: m_offset_x = 500000; m_offset_y = 0; m_scale = 0.996; m_center_lon = -1; break;
            }
        }
        RectangleCoord(double _x, double _y, double _scale) : m_offset_x(_x), m_offset_y(_y), m_scale(_scale), m_center_lon(-1) {}

        void setCenterLon(double _lon) {m_center_lon = _lon;}

        double x() const noexcept {return m_offset_x;}
        double y() const noexcept {return m_offset_y;}
        double scale() const noexcept {return m_scale;}
        double centerLon() const noexcept {return m_center_lon;}

    private:
        double m_offset_x, m_offset_y, m_scale, m_center_lon;
    };

    // convert function
    // all application use one instance, so singleton pattern ?
    class Convert {
    public:
        Convert(const Ellipsoid& in) { 
            ellip = in; 
        }
        Convert(const Ellipsoid& _ellip, const RectangleCoord& _rect) : ellip(_ellip), rect(_rect) {
            utm = new GenLas::Mercartor(_ellip.a(), _ellip.b(),rect.centerLon(), rect.scale(),rect.x(), rect.y());
        }
        ~Convert() {
            if (utm != nullptr) {
                delete utm;
                utm = nullptr;
            }
        }

        LLA ecef2lla(const ECEF& in) {
            double p = 0.0, slat = 0.0, N = 0.0, htold = 0.0, latold = 0.0;
            double e = ellip.e();
            e = e * e;

            int  i = 0;
            double tmp = 0.0;

            LLA out;
            //Check postion valiable
            tmp = in.distance(ECEF(0.0, 0.0, 0.0));
            if (fabs(tmp) < ellip.a()*0.5)
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
                N = ellip.a() / sqrt(1.0 - e * slat*slat);
                htold = out.alt;
                out.alt = p / cos(out.lat) - N;

                latold = out.lat;
                out.lat = atan2(in.z, p*(1.0 - e * (N / (N + out.alt))));
                if (fabs(out.lat - latold) < 1.0e-9 &&
                    fabs(out.alt - htold) < (1.0e-9 * ellip.a()))
                    break;
            }

            out.lon = atan2(in.y, in.x);
            return out;
        }

        ECEF lla2ecef(const LLA& in) {
            double n;
            ECEF out;

            n = (ellip.a()*ellip.a()) / sqrt(
                ellip.a()*ellip.a()*cos(in.lat)*cos(in.lat) +
                ellip.b() * ellip.b()*sin(in.lat)*sin(in.lat));

            out.x = (n + in.alt)*cos(in.lat)*cos(in.lon);
            out.y = (n + in.alt)*cos(in.lat)*sin(in.lon);
            out.z = ((ellip.b()*ellip.b()) / (ellip.a()*ellip.a())*n
                + in.alt) * sin(in.lat);

            return out;
        }

        XYZ lla2xyz(const LLA& lla) {
            if (utm == nullptr)
                return XYZ{};
            return utm->lla2xyz(lla);
        }

        LLA xyz2lla(const XYZ& xyz) {
            if (utm == nullptr)
                return LLA{};
            return utm->xyz2lla(xyz);
        }
    private:
        Ellipsoid ellip;
        RectangleCoord rect;
        GenLas::Mercartor *utm = nullptr;
    };

    
};
/*
 * @Descripttion:   Coordinate convert namespace 
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-08-01 17:22:21
 * @LastEditors: Sean
 * @LastEditTime: 2021-08-01 18:21:50
 */

// c++ stl
#include <iostream>
#include <cmath>
#include <unordered_map>

// 3rd
#include <glog/logging.h>

// struct def
#include "StructDef.h"

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
        }
        Ellipsoid(double _major, double _minor) : axis_a(_major), axis_b(_minor) {}
        ~Ellipsoid() = default;

        double a()  noexcept {return this->axis_a;}
        double b()  noexcept {return this->axis_b;}
    private:
        double axis_a, axis_b;
        
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

        double x() noexcept {return m_offset_x;}
        double y() noexcept {return m_offset_y;}
        double scale() noexcept {return m_scale;}
        double centerLon() noexcept {return m_center_lon;}

    private:
        double m_offset_x, m_offset_y, m_scale, m_center_lon;
    };

    // convert function
    // all application use one instance, so singleton pattern ?
    class Convert {
    public:
        Convert(const Ellipsoid& in) { ellip = in; }
        Convert(const Ellipsoid& _ellip, const RectangleCoord& _rect) : ellip(_ellip), rect(_rect) {}
        ~Convert() {}


    private:
        Ellipsoid ellip;
        RectangleCoord rect;
    };
};
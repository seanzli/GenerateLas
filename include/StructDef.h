/*
 * @Description: Basic Struct Defind
 * @Author: Sean
 * @Date: 2021-07-13 21:24:46
 * @LastEditTime: 2021-07-15 21:50:56
 * @LastEditors: Sean
 * @Reference: 
 */
#pragma once

#include <cmath>

// using namespace ??

template<class T> // should be float or double
struct Point
{
    T x;
    T y;
    T z;

    Point():x(0.0), y(0.0), z(0.0) {}
    Point(const T& _x, const T& _y, const T& _z) : x(_x), y(_y), z(_z) {}

    template<class U>
    const Point operator+(const Point<U>& a) const{
        Point<T> out;
        out.x = this->x + a.x;
        out.y = this->y + a.y;
        out.z = this->z + a.z;
        return out;
    }

    template<class U>
    const Point operator-(const Point<U>& a) const{
        Point<T> out;
        out.x = this->x - a.x;
        out.y = this->y - a.y;
        out.z = this->z - a.z;
        return out;
    }

    template<class U>
    const T distance(const Point<U>& a) const {
        Point out = (*this) - a;
        return sqrt(out.x*out.x + out.y*out.y + out.z*out.z);
    }

    friend std::ostream &operator<<(std::ostream& out ,const Point<T>& op)
    {
        out << "value: x = " << op.x << " ,y = " << op.y << " ,z = " << op.z << std::endl;
        return out;
    }

};

template<class T>
struct LidarPoint{
    Point<T> point;
    
    double gps_time;
    unsigned char returnNumber;
    unsigned char numbersOfReturns;
    unsigned char ref;
    unsigned char reserve;
    
    LidarPoint() = default;
};

using ATT  = Point<double>; // roll pitch heading;
using ECEF = Point<double>;
using VAL  = Point<double>;

struct LLA {
    double lat;
    double lon;
    double alt;
    LLA(double _lat, double _lon, double _alt) : lat(_lat), lon(_lon), alt(_alt) {}
};

struct Traj {
    double gps_time;
    ECEF pos;
    ATT att;
    VAL val;
    Traj() = default;
};
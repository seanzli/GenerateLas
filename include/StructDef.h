/*
 * @Description: Basic Struct Defind
 * @Author: Sean
 * @Date: 2021-07-13 21:24:46
 * @LastEditTime: 2021-07-25 12:57:36
 * @LastEditors: Sean
 * @Reference: 
 */
#pragma once

#include <cmath>

// using namespace ??

const unsigned int SECENDS_IN_DAY = 86400;

template<class T> // should be float or double
struct Point
{
    union {
        T x;
        T roll;
        T lat;
    };
    union {
        T y;
        T pitch;
        T lon;
    };
    union {
        T z;
        T heading;
        T alt;
    };

    Point():x(0.0), y(0.0), z(0.0) {}
    Point(const T& _x, const T& _y, const T& _z) : x(_x), y(_y), z(_z) {}
    Point(const Point<T>& in) {
        this->x = in.x;
        this->y = in.y;
        this->z = in.z;
    }

    Point& operator=(const Point<T>& a) {
        this->x = a.x;
        this->y = a.y;
        this->z = a.z;
        return (*this);
    }

    Point operator*(const double a) {
        return Point(this->x*a, this->y*a, this->z*a);
    }

    Point operator/(const double a) {
        return Point(this->x/a, this->y/a, this->z/a);
    }

    template<class U>
    Point operator+(const Point<U>& a) const{
        return Point(this->x + a.x, this->y + a.y, this->z + a.z);
    }

    template<class U>
    Point operator-(const Point<U>& a) const{
        return Point(this->x - a.x, this->y - a.y, this->z - a.z);
    }

    const bool operator==(const Point<T>& a) const{
        return (abs(a.x - this->x) < 1e-4 &&
                abs(a.y - this->y) < 1e-4 &&
                abs(a.z - this->z) < 1e-4);
    }

    template<class U>
    T distance(const Point<U>& a) const {
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
class LidarPoint{
public:
    Point<T> point;
    
    double gps_time;
    unsigned char returnNumber;
    unsigned char numbersOfReturns;
    unsigned char ref;
    unsigned char reserve;
    
    LidarPoint() = default;
};

using ECEF = Point<double>; // meters
using VAL  = Point<double>; // m/s
using LLA  = Point<double>;
using ATT  = Point<double>;


struct Traj {
    double gps_time;
    ECEF pos;
    ATT att;
    VAL val;
    Traj() = default;
};

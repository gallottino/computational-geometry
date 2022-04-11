#pragma once
#include<list>
#include <string>
#include <sstream>

namespace geometry{

    class Point2D
    {
        public:
        double x;
        double y;

        Point2D(double x, double y) : x(x), y(y){}

        std::string toString() const {
            std::stringstream ss;
            ss << "("<< x << "," << y << ")";
            return ss.str();
        }

        bool operator==(Point2D p) {
            return x == p.x && y == p.y;
        }
    };

    class Segment2D{
        public:
        Point2D start;
        Point2D end;
    };
}
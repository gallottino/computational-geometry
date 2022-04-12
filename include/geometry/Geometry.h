#pragma once
#include <algorithm>
#include <list>
#include <math.h>
#include <string>
#include <sstream>

namespace geometry{

    enum Orientation {
        COUNTERCLOCKWISE,
        CLOCKWISE,
        COLLINEAR
    };

    class Point2D
    {
        public:
        double x;
        double y;
        bool null_value;

        Point2D(double x, double y) : x(x), y(y) {
            null_value = false;
        }

        Point2D() {
            null_value = true;
        }

        std::string toString() const {
            std::stringstream ss;
            ss << "("<< x << "," << y << ")";
            return ss.str();
        }

        bool operator==(const Point2D p) const {
            return x == p.x && y == p.y;
        }

        bool operator<(const Point2D p) const {
            return y == p.y ? x < p.x : y < p.y;
        }

        bool operator<(const Point2D* p) const {
            return y == p->y ? x < p->x : y < p->y;
        }
    };

    class Segment2D{
        public:
        Point2D start;
        Point2D end;

        Segment2D(Point2D start, Point2D end) : start(start), end(end) {}
        
        bool operator<(const Segment2D p) const {
            return start == p.start ? end < p.end : start < p.start;
        }

        bool operator<(const Segment2D* p) const {
            return start == p->start ? end < p->end : start < p->start;
        }

        bool onSegment(Point2D p) {
           return p.x <= std::max(start.x, end.x) && p.x >= std::min(start.x, end.x) &&
                p.y <= std::max(start.y, end.y) && p.y >= std::min(start.y, end.y);
        }

        Point2D intersectSegment2D(Segment2D s1, Segment2D s2) const {
            double A1 = s1.end.y - s1.start.y;
            double B1 = s1.start.x - s1.end.x;
            double C1 = A1 * s1.start.x + B1 * s1.start.y;
            double A2 = s2.end.y - s2.start.y;
            double B2 = s2.start.x - s2.end.x;
            double C2 = A2 * s2.start.x + B2 * s2.start.y;

            double denominator = A1 * B2 - A2 * B1;
            if(denominator == 0) {
                return Point2D();
            }

            double x = (B2 * C1 - B1 * C2) / denominator;
            double y = (A1 * C2 - A2 * C1) / denominator;

            Point2D intersectPoint = Point2D(x, y);
            if(s1.onSegment(intersectPoint) && s2.onSegment(intersectPoint)) 
                return intersectPoint;
            return Point2D();
        }

    };
}
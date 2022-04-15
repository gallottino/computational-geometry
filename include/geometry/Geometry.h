#pragma once
#include <algorithm>
#include <iostream>
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
            x = -1;
            y = -1;
            null_value = true;
        }

        std::string toString() const {
            std::stringstream ss;
            ss << "("<< x << "," << y << ")";
            return ss.str();
        }

        bool operator==(const Point2D p) const {
            return abs(x - p.x) < 0.0001f && abs(y - p.y) < 0.0001f;
        }

        bool operator!=(const Point2D p) const {
            return x != p.x || y != p.y;
        }
        Point2D& operator=(const Point2D& p) {
            x = p.x;
            y = p.y;
        }

        bool operator<(const Point2D p) const {
            return y == p.y ? x < p.x : y < p.y;
        }

        bool operator>(const Point2D p) const {
            return y == p.y ? x > p.x : y > p.y;
        }

        double getDistance(Point2D p1, Point2D p2) {
            return sqrt(pow(p2.x - p1.x , 2) +  pow(p2.y - p1.y,2));
        }

        static bool makeRightTurn( Point2D first, Point2D middle, Point2D last) {
            return (middle.y - first.y) * (last.x - middle.x) - (middle.x - first.x) * (last.y - middle.y) > 0;
        }

        static bool isLeft(Point2D a, Point2D b, Point2D c){
            return ((b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x)) > 0;
        }
    };

    std::ostream& operator<<(std::ostream& output, Point2D& p) {
        output << p.toString();
        return output;
    }

    class Segment2D{
        public:
        Point2D start;
        Point2D end;


        Segment2D(Point2D start, Point2D end) : start(start), end(end) {}

        Segment2D twin() {
            return Segment2D(end,start);
        }

        bool operator<(const Segment2D p) const {
            return start.x == p.start.x ? start.y < p.start.y : start.x < p.start.x;
        }

        bool operator>(const Segment2D p) const {
            return start.x == p.start.x ? start.y > p.start.y : start.x > p.start.x;
        }

        bool onSegment(Point2D p) {
           return p.x <= std::max(start.x + 0.0001f, end.x + 0.0001f) && p.x >= std::min(start.x - 0.0001f, end.x - 0.0001f) &&
                p.y <= std::max(start.y + 0.0001f, end.y + 0.0001f) && p.y >= std::min(start.y - 0.0001f, end.y - 0.0001f);
        }

        bool containsPoint(Point2D p) {
            if(start == p || end == p) return false;
            double a = p.getDistance(start,p);
            double b = p.getDistance(end,p);
            double c = p.getDistance(start,end);

            return a + b == c;
        }
        
        bool operator==(Segment2D s) {
            return (start == s.start && end == s.end) || (start == s.end && end == s.start);
        }

        Segment2D operator=(const Segment2D& s) const {
            Segment2D res(s.start,s.end);
            return res;
        }

        bool operator!=(Segment2D s) {
            return !(twin() == s);
        }

        static Point2D intersectSegment2D(Segment2D s1, Segment2D s2) {
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

    std::ostream& operator<<(std::ostream& output, Segment2D& s) {
        output << s.start.toString() << "->" << s.end.toString();
        return output;
    }
}
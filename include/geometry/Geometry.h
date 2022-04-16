#pragma once
#include <algorithm>
#include <iostream>
#include <list>
#include <math.h>
#include <string>
#include <sstream>

namespace geometry{

    class Point2D
    {
        public:
        double x;
        double y;
        bool null_value;

        Point2D();
        Point2D(double x, double y);

        std::string toString() const;

        Point2D& operator=(const Point2D& p);
        bool operator==(const Point2D p) const;
        bool operator!=(const Point2D p) const;
        bool operator<(const Point2D p) const;
        bool operator>(const Point2D p) const;
        
        static double getDistance(Point2D p1, Point2D p2);

        static bool makeRightTurn( Point2D first, Point2D middle, Point2D last);
        static bool isLeft(Point2D a, Point2D b, Point2D c);
    };

    class Segment2D{
        public:
        Point2D start;
        Point2D end;

        Segment2D(Point2D start, Point2D end);

        Segment2D twin();
        Segment2D operator=(const Segment2D& s) const;

        bool operator==(Segment2D s) const;
        bool operator!=(Segment2D s);
        bool operator<(const Segment2D p) const;
        bool operator>(const Segment2D p) const;
        bool onSegment(Point2D p) const;

        bool containsPoint(Point2D p) const;

        static Point2D intersectSegment2D(Segment2D s1, Segment2D s2);
    };
}
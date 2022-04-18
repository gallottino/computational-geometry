//########################################
// Project: Galmetry Sandbox
// Author: Gallottino
// Last modified: 16-04-2022
//#########################################

#pragma once

#include <algorithm>
#include <iostream>
#include <list>
#include <math.h>
#include <string>
#include <sstream>

namespace geometry{

    namespace Delta {
        const float Delta1 = 0.1f;
        const float Delta2 = 0.01f;
        const float Delta3 = 0.001f;
        const float Delta4 = 0.0001f;
        const float Delta5 = 0.00001f;
        const float Delta6 = 0.000001f;
        const float Delta7 = 0.0000001f;
    };

    /**
     * @brief 
     * It rapresents a Point in 2D space with x and y coordinates.\\
     * Istance of a Point2D without parameters is equal to null point
     * 
     * @details description
     * example:
     * Point2D p(100,20)
     * 
     * ^ y
     * |
     * |            
     * |   
     * |             . (100,20)
     * |
     * |--------------------> 
     *                     x
     */
    class Point2D {
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
    typedef Point2D Vertex2D;

    /**
     * @brief 
     * It rapresents a Segment in 2D space with a start and end Point.
     * 
     * @details
     * start point is the one with the greatest y-coordinate.
     * end point is the one with the smallest y-coordinate.
     */
    class Segment2D {
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
    typedef Segment2D HalfEdge;
}
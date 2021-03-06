

#pragma once

#include <geometry/Geometry.hpp>
#include <vector>
namespace geometry {

    /***
     * MonotoneConvexHull is described in Chapter 1 in the book "Computational Geometry" by Mark de Berg
    ***/
    class MonotoneConvexHull {
        public:
        std::vector<Point2D> convexHull;

        MonotoneConvexHull();
        MonotoneConvexHull(std::vector<Point2D> newPoints);

        void resetPoints(std::vector<Point2D> newPoints);
        void calculate();
        bool makeRightTurn( Point2D first, Point2D middle, Point2D last);

        private: 
        int step;
        int offset;
        bool running;
        std::vector<Point2D> points;
    };
};
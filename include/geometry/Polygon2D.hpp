#pragma once

#include <geometry/Geometry.hpp>
#include <vector>

namespace geometry {
    class Polygon2D {

        public:
        Polygon2D(std::vector<Point2D> vertices);
        std::vector<Point2D> vertices;
    };
}
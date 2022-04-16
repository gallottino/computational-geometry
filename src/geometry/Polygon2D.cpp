#include <geometry/Polygon2D.hpp>

namespace geometry {

    Polygon2D::Polygon2D(std::vector<Point2D> vertices) {
        this->vertices = vertices;
    }
}
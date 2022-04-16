#include <geometry/Geometry.hpp>

namespace geometry{
Point2D::Point2D(double x, double y) : x(x), y(y) {
    null_value = false;
}

Point2D::Point2D() {
    x = -1;
    y = -1;
    null_value = true;
}

std::string Point2D::toString() const {
    std::stringstream ss;
    ss << "("<< x << "," << y << ")";
    return ss.str();
}

Point2D& Point2D::operator=(const Point2D& p) {
    x = p.x;
    y = p.y;
}

bool Point2D::operator==(const Point2D p) const {
    return abs(x - p.x) < 0.0001f && abs(y - p.y) < 0.0001f;
}


bool Point2D::operator!=(const Point2D p) const {
    return x != p.x || y != p.y;
}

bool Point2D::operator<(const Point2D p) const {
    return y == p.y ? x < p.x : y < p.y;
}

bool Point2D::operator>(const Point2D p) const {
    return y == p.y ? x > p.x : y > p.y;
}

double Point2D::getDistance(Point2D p1, Point2D p2) {
    return sqrt(pow(p2.x - p1.x , 2) +  pow(p2.y - p1.y,2));
}

bool Point2D::makeRightTurn( Point2D first, Point2D middle, Point2D last) {
    return (middle.y - first.y) * (last.x - middle.x) - (middle.x - first.x) * (last.y - middle.y) > 0;
}

bool Point2D::isLeft(Point2D a, Point2D b, Point2D c){
    return ((b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x)) > 0;
}
};

#include <geometry/Geometry.h>

namespace geometry {

    Segment2D::Segment2D(Point2D start, Point2D end) 
    : start(start), end(end) {

    }

    Segment2D Segment2D::twin() {
        return Segment2D(end,start);
    }

    bool Segment2D::operator<(const Segment2D p) const {
        return start.x == p.start.x ? start.y < p.start.y : start.x < p.start.x;
    }

    bool Segment2D::operator>(const Segment2D p) const {
        return start.x == p.start.x ? start.y > p.start.y : start.x > p.start.x;
    }

    bool Segment2D::onSegment(Point2D p) const {
        return p.x <= std::max(start.x + 0.0001f, end.x + 0.0001f) && p.x >= std::min(start.x - 0.0001f, end.x - 0.0001f) &&
            p.y <= std::max(start.y + 0.0001f, end.y + 0.0001f) && p.y >= std::min(start.y - 0.0001f, end.y - 0.0001f);
    }

    bool Segment2D::containsPoint(Point2D p) const {
        if(start == p || end == p) return false;
        double a = p.getDistance(start,p);
        double b = p.getDistance(end,p);
        double c = p.getDistance(start,end);

        return a + b == c;
    }
    
    bool Segment2D::operator==(Segment2D s) const {
        return (start == s.start && end == s.end) || (start == s.end && end == s.start);
    }

    Segment2D Segment2D::operator=(const Segment2D& s) const {
        Segment2D res(s.start,s.end);
        return res;
    }

    bool Segment2D::operator!=(Segment2D s) {
        Segment2D twin_check = twin();
        return !(twin_check == s);
    }

    Point2D Segment2D::intersectSegment2D(Segment2D s1, Segment2D s2) {
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
}
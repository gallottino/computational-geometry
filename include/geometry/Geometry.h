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
           return p.x <= std::max(start.x, end.x) && p.x >= std::min(start.x, end.x) &&
                p.y <= std::max(start.y, end.y) && p.y >= std::min(start.y, end.y);
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

    std::ostream& operator<<(std::ostream& output, Segment2D& s) {
        output << s.start.toString() << "->" << s.end.toString();
        return output;
    }

    class Segment2DEvent {
        public:
        Point2D eventPoint;
        Segment2D seg;

        Segment2DEvent(Segment2D segment, Point2D event) : seg(segment), eventPoint(event) { }

        Segment2D getSweepLine(Point2D event) {
            Point2D start(0,event.y);
            Point2D end(1000, event.y);

            return Segment2D(start,end);
        }
        bool operator<(Segment2DEvent segEvent) {             
            Point2D currentEvent =  segEvent.eventPoint.y > eventPoint.y ? segEvent.eventPoint : eventPoint;

            Point2D intersectP = seg.intersectSegment2D(seg, getSweepLine(currentEvent));
            Point2D intersectP2 = segEvent.seg.intersectSegment2D(segEvent.seg, getSweepLine(currentEvent));
            return intersectP < intersectP2;
        }

        bool operator==(Segment2DEvent segEvent) {             
            Segment2D s1 = seg;
            Segment2D s2 = segEvent.seg;
            return s1 == s2;
        }

        Segment2DEvent operator=(Segment2DEvent segEvent) {       
            Segment2DEvent newSegEvent(segEvent.seg,segEvent.eventPoint);      
        }

        bool operator!=(Segment2DEvent segEvent) {             
            Segment2D s1 = seg;
            Segment2D s2 = segEvent.seg;
            return s1 != s2;
        }

    };   

    std::ostream& operator<<(std::ostream& output, Segment2DEvent& s) {
        output << s.seg.start.toString() << "----" << s.seg.end.toString();
        return output;
    }
}
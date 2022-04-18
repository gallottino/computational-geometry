#pragma once

#include <geometry/Geometry.hpp>
#include <set>
#include <map>
#include <vector>

namespace geometry {

    class StatusPlaneSweep {

        public:
        Segment2D segment;
        Point2D eventPoint;

        StatusPlaneSweep(Segment2D seg, Point2D point) : 
            segment(seg), eventPoint(point) {}
    };

    struct CompareStatus {
        
        bool operator()(StatusPlaneSweep s1,StatusPlaneSweep s2) {
            if(s1.segment == s2.segment) return false;

            auto comparePoint2D = [] (Point2D p1, Point2D p2) 
                -> bool {return abs(p1.x - p2.x) < Delta::Delta6 ? p1.y < p2.y : p1.x < p2.x;};

            Point2D currentPoint = s1.eventPoint.y > s2.eventPoint.y ? s1.eventPoint : s2.eventPoint;
            if(s1.segment.end == currentPoint || s2.segment.end == currentPoint) return false;

            Segment2D sweepLine(Segment2D(Point2D(0.0,currentPoint.y), Point2D(1000.0, currentPoint.y)));
            
            Point2D sweep_s1 = Segment2D::intersectSegment2D(s1.segment, sweepLine);
            Point2D sweep_s2 = Segment2D::intersectSegment2D(s2.segment, sweepLine);

            return comparePoint2D(sweep_s1,sweep_s2);
        }
    };

    class PlaneSweep{
        
        public:
        Point2D eventPoint;  
        std::vector<Point2D> intersectPoints;

        PlaneSweep(std::vector<Segment2D> segments);

        void init(std::vector<Segment2D> segments);
        void calculate();
        void handleEventPoint(Point2D event);
        void findNewEvent(Segment2D sl, Segment2D sr, Point2D p);

        private:
        Point2D lastEventPoint;
        std::set<Point2D> queue;
        std::set<StatusPlaneSweep, CompareStatus> status;
                                
        std::map<Point2D, std::vector<Segment2D>> U;
        std::map<Point2D, std::vector<Segment2D>> C;
        std::map<Point2D, std::vector<Segment2D>> L;
    };

}
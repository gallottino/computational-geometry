#pragma once

#include <geometry/Geometry.h>
#include <set>
#include <map>
#include <vector>

namespace geometry {

    class StatusPlaneSweep {

        public:
        Segment2D segment;
        Point2D eventPoint;

        bool operator<(StatusPlaneSweep s2) {
            Point2D currentPoint = eventPoint.y > s2.eventPoint.y ? eventPoint : s2.eventPoint;

            Segment2D sweepLine(Segment2D(Point2D(0.0,currentPoint.y), Point2D(1000.0, currentPoint.y)));

            Point2D sweep_s1 = segment.intersectSegment2D(segment, sweepLine);
            Point2D sweep_s2 = s2.segment.intersectSegment2D(s2.segment ,sweepLine);
            
            return sweep_s1 < sweep_s2;
        }

        StatusPlaneSweep(Segment2D seg, Point2D point) : 
            segment(seg), eventPoint(point) {}
    };

    struct CompareStatus {

        bool operator()(StatusPlaneSweep s1,StatusPlaneSweep s2) {
            Point2D currentPoint = s1.eventPoint > s2.eventPoint? s1.eventPoint : s2.eventPoint;

            Segment2D sweepLine(Segment2D(Point2D(0.0,currentPoint.y), Point2D(1000.0, currentPoint.y)));

            Point2D sweep_s1 = s1.segment.intersectSegment2D(s1.segment, sweepLine);
            Point2D sweep_s2 = s2.segment.intersectSegment2D(s2.segment ,sweepLine);
            
            return sweep_s1 < sweep_s2;
        }
    };

    class PlaneSweep{
        
        public:
        Point2D eventPoint;

        std::set<Point2D> queue;
        std::vector<Point2D> intersectPoints;
        std::set<StatusPlaneSweep, CompareStatus> status;
        
        std::map<Point2D, std::set<Segment2D>> U;
        std::map<Point2D, std::set<Segment2D>> C;
        std::map<Point2D, std::set<Segment2D>> L;

        PlaneSweep(std::vector<Segment2D> segments) {
            init(segments);
        }

        void init(std::vector<Segment2D> segments) {
            U.clear();
            L.clear();
            C.clear();
            queue.clear();
            status.clear();
            intersectPoints.clear();

            for(Segment2D seg : segments) {
                queue.insert(seg.start);
                U[seg.start].insert(seg);

                queue.insert(seg.end);
                L[seg.end].insert(seg);
            }
            eventPoint = Point2D();
        }

        void calculate() {  
            if(queue.size() > 0){
                eventPoint = *queue.begin(); queue.erase(eventPoint);
                handleEventPoint(eventPoint);
            }
        }
            
        void handleEventPoint(Point2D event) {
            
            for(Segment2D s : L[event]) {
                StatusPlaneSweep toRemove(s, event);
                status.erase(toRemove);
            }

            for(Segment2D s : C[event]) {
                StatusPlaneSweep toSwap(s, event);
                status.erase(toSwap);
                status.insert(toSwap);
            }

            for(Segment2D s : U[event]) {
                StatusPlaneSweep toInsert(s, event);
                status.insert(toInsert);
            }

            std::set<Segment2D> U_C;
            std::set_union( U[event].begin(),U[event].end(),
                            C[event].begin(),C[event].end(),
                            std::inserter(U_C,U_C.begin()));

            std::cout << "\nSweep Line Status: " << status.size() << std::endl;

            for(StatusPlaneSweep s : status) {
                std::cout << s.segment << std::endl;
            }

            std::cout << "\n";
            if(U_C.size() == 0) {
                if(status.size() < 2) return;

                auto middle_ptr = status.begin();
                std::advance(middle_ptr, status.size() / 2 - 1);

                auto right_middle = middle_ptr;
                std::advance(right_middle, 1);

                findNewEvent(middle_ptr->segment, right_middle->segment, event);
            } else {
                if(status.size() < 2) return;

                
            }
        }

        Point2D findNewEvent(Segment2D sl, Segment2D sr, Point2D p) {   
            Point2D intersectPoint = sl.intersectSegment2D(sl,sr);

            if(!intersectPoint.null_value && intersectPoint.y > p.y){
                queue.insert(intersectPoint);
                intersectPoints.push_back(intersectPoint);
                C[intersectPoint].insert(sl);
                C[intersectPoint].insert(sr);
            }
        }
    };

}
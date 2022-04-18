#include <algorithm/PlaneSweep.hpp>

namespace geometry {
    PlaneSweep::PlaneSweep(std::vector<Segment2D> segments) {
        init(segments);
    }

    void PlaneSweep::init(std::vector<Segment2D> segments) {
        U.clear();
        L.clear();
        C.clear();
        queue.clear();
        status.clear();
        intersectPoints.clear();

        for(Segment2D seg : segments) {
            queue.insert(seg.start);
            U[seg.start].push_back(seg);

            queue.insert(seg.end);
            L[seg.end].push_back(seg);
        }
        eventPoint = Point2D();
    }

    void PlaneSweep::calculate() {  
        while(queue.size() > 0){
            eventPoint = *queue.begin(); queue.erase(eventPoint);
            handleEventPoint(eventPoint);
            lastEventPoint = eventPoint;
        }
    }
            
    void PlaneSweep::handleEventPoint(Point2D event) {

        for(Segment2D s : C[event]) {
            StatusPlaneSweep toRemove(s, lastEventPoint);
            status.erase(toRemove);
        }

        for(Segment2D s : U[event]) {
            StatusPlaneSweep toInsert(s, event);
            status.insert(toInsert);
        }

        for(Segment2D s : C[event]) {
            StatusPlaneSweep toInsert(s, Point2D(event.x, event.y + 0.001f));
            status.insert(toInsert);
        }

        if(U[event].size() + C[event].size() == 0) {
            if(status.size() < 2) return;

            StatusPlaneSweep toRemove(L[event][0], lastEventPoint);
            
            auto left = status.lower_bound(toRemove);
            auto right = status.upper_bound(toRemove);

            Segment2D left_seg = (--left)->segment;
            Segment2D right_seg = right->segment;
            findNewEvent(left->segment, right->segment, event);
            status.erase(toRemove);
            
        } else {
            if(status.size() < 2) return;

            Segment2D leftmost = U[event].size() == 0 ? C[event][0] : U[event][0];
            auto left_leftmost_ptr = status.find(StatusPlaneSweep(leftmost,event));
            if(left_leftmost_ptr != status.begin()) {
                left_leftmost_ptr--;
                Segment2D left = left_leftmost_ptr->segment;
                Segment2D right = leftmost;
                findNewEvent(left,right, event);
            }

            Segment2D rightmost = U[event].size() == 0 ? C[event][1] : U[event][0];
            auto right_rightmost_ptr = status.find(StatusPlaneSweep(rightmost,event));
            right_rightmost_ptr++;
            if(right_rightmost_ptr != status.end() ) {
                Segment2D left = rightmost;
                Segment2D right = right_rightmost_ptr->segment;
                findNewEvent(left,right, event);
            }
        }
    }

    void PlaneSweep::findNewEvent(Segment2D sl, Segment2D sr, Point2D p) {   
        Point2D intersectPoint = sl.intersectSegment2D(sl,sr);

        if(!intersectPoint.null_value && intersectPoint.y > p.y){
            queue.insert(intersectPoint);
            intersectPoints.push_back(intersectPoint);
            C[intersectPoint].push_back(sr);
            C[intersectPoint].push_back(sl);
        }
    }
}
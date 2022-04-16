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
        Point2D lastEventPoint;
        Point2D eventPoint;

        std::set<Point2D> queue;
        std::vector<Point2D> intersectPoints;
        std::set<StatusPlaneSweep, CompareStatus> status;
        
        std::map<Point2D, std::vector<Segment2D>> U;
        std::map<Point2D, std::vector<Segment2D>> C;
        std::map<Point2D, std::vector<Segment2D>> L;

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
                U[seg.start].push_back(seg);

                queue.insert(seg.end);
                L[seg.end].push_back(seg);
            }
            eventPoint = Point2D();
        }

        void calculate() {  
            while(queue.size() > 0){
                eventPoint = *queue.begin(); queue.erase(eventPoint);
                handleEventPoint(eventPoint);
                lastEventPoint = eventPoint;
            }
        }
            
        void handleEventPoint(Point2D event) {

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

        Point2D findNewEvent(Segment2D sl, Segment2D sr, Point2D p) {   
            Point2D intersectPoint = sl.intersectSegment2D(sl,sr);

            if(!intersectPoint.null_value && intersectPoint.y > p.y){
                queue.insert(intersectPoint);
                intersectPoints.push_back(intersectPoint);
                C[intersectPoint].push_back(sr);
                C[intersectPoint].push_back(sl);
            }
        }

        void drawPoint(sf::RenderWindow& window, Point2D p, sf::Color color) {
            float radius = 3.f;

            if(p.null_value) return;

            sf::CircleShape shape;
            shape.setRadius(radius);
            shape.setFillColor(color);
            shape.setOutlineColor(color);
            shape.setOutlineThickness(1.f);
            shape.move(p.x - radius,p.y - radius);
            window.draw(shape);
        }

        void drawIntersectionPoints(sf::RenderWindow& window) {

            for(StatusPlaneSweep s : status) {
                Segment2D sweepLine(Segment2D(Point2D(0.0,eventPoint.y), Point2D(1000.0, eventPoint.y)));
                drawPoint(window, Segment2D::intersectSegment2D(s.segment, sweepLine), sf::Color::Magenta);
            }
        }

    };

}
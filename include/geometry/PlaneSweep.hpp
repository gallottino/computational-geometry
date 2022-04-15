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

        StatusPlaneSweep(Segment2D seg, Point2D point) : 
            segment(seg), eventPoint(point) {}
    };

    struct CompareStatus {
        
        bool operator()(StatusPlaneSweep s1,StatusPlaneSweep s2) {
            if(s1.segment == s2.segment) return false;

            auto comparePoint2D = [] (Point2D p1, Point2D p2) 
                -> bool {return abs(p1.x - p2.x) < 0.0001f ? p1.y < p2.y : p1.x < p2.x;};

            Point2D currentPoint = s1.eventPoint.y > s2.eventPoint.y ? s1.eventPoint : s2.eventPoint;
            if(s1.segment.end == currentPoint || s2.segment.end == currentPoint) return false;

            Segment2D sweepLine(Segment2D(Point2D(0.0,currentPoint.y), Point2D(1000.0, currentPoint.y)));
            
            Point2D sweep_s1 = Segment2D::intersectSegment2D(s1.segment, sweepLine);
            Point2D sweep_s2 = Segment2D::intersectSegment2D(s2.segment, sweepLine);

            if(sweep_s1.null_value) {

                return false;
                std::cout << "NULL VALUE" << s1.segment << ", " << currentPoint << "   point: " << sweep_s1 << std::endl;
            }

            if(sweep_s2.null_value) {
                return true;
                std::cout << "NULL VALUE" << s2.segment << ", " << currentPoint <<"   point: " << sweep_s2 <<  std::endl;
            }


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
            if(queue.size() > 0){
                eventPoint = *queue.begin(); queue.erase(eventPoint);
                handleEventPoint(eventPoint);
                lastEventPoint = eventPoint;
            }
        }
            
        void handleEventPoint(Point2D event) {
            for(Segment2D s : L[event]) {
                StatusPlaneSweep toRemove(s, lastEventPoint);
                status.erase(toRemove);
            }

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

            std::cout << "-------------------------------------\nEvent Point : "<< event << std::endl;
            std::cout << "Sweep Line Status: " << status.size() << std::endl;

            for(StatusPlaneSweep s : status) {
                std::cout << s.segment << std::endl;
            }

            std::cout << "\n";
            if(U[event].size() + C[event].size() == 0) {
                if(status.size() < 2) return;

                StatusPlaneSweep toRemove(L[event][0], lastEventPoint);
                auto middle_ptr = status.lower_bound(toRemove);

                auto right_middle = middle_ptr;
                right_middle++;
                Segment2D left = middle_ptr->segment;
                Segment2D right = right_middle->segment;
                if(right_middle == status.end()) {
                    left = (--middle_ptr)->segment;
                    right = (--right_middle)->segment;
                }
                
                std::cout << "TEST AROUND A POINT: " << left << " with " << right << std::endl;
                findNewEvent(middle_ptr->segment, right_middle->segment, event);
            } else {
                if(status.size() < 2) return;
    
                Segment2D leftmost = U[event].size() == 0 ? C[event][0] : U[event][0];
                std::cout << "To test" << leftmost << std::endl;
                auto left_leftmost_ptr = status.find(StatusPlaneSweep(leftmost,event));
                if(left_leftmost_ptr != status.begin()) {
                    left_leftmost_ptr--;
                    Segment2D left = left_leftmost_ptr->segment;
                    Segment2D right = leftmost;
                    std::cout << "TEST LEFTMOST" << left << ", " << right << std::endl;
                    findNewEvent(left,right, event);
                }

                Segment2D rightmost = U[event].size() == 0 ? C[event][1] : U[event][0];
                std::cout << "To test" << rightmost << std::endl;
                auto right_rightmost_ptr = status.find(StatusPlaneSweep(rightmost,event));
                right_rightmost_ptr++;
                if(right_rightmost_ptr != status.end() ) {
                    Segment2D left = rightmost;
                    Segment2D right = right_rightmost_ptr->segment;
                    std::cout << "TEST RIGHTMOST" << left << ", " << right << std::endl;
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
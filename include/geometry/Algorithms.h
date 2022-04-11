#pragma once
#include <geometry/Geometry.h>

#include <algorithm>
#include <iostream>
#include <memory>
#include <set>
#include <vector>
#include <queue>

namespace geometry {

    static bool compareSharedPoint2D(std::shared_ptr<Point2D> p1, std::shared_ptr<Point2D>  p2){   
        return p1->x == p2->x ? p1->y < p2->y : p1->x < p2->x;
    }

    static bool comparePoint2D(Point2D p1, Point2D  p2){   
        return p1.x == p2.x ? p1.y < p2.y : p1.x < p2.x;
    }
    
    static bool Point2dInSegment2D(Point2D p, Segment2D seg) {
        if(p.x < seg.start.x || p.x > seg.end.x) return false;
        if(p.y < seg.start.y || p.y > seg.end.y) return false;


    }

    namespace algorithm {
        
        /***
         * MonotoneConvexHull is described in Chapter 1 in the book "Computational Geometry" by Mark de Berg
         **/
        class MonotoneConvexHull {
            public:
            static std::vector<std::shared_ptr<Point2D>> calculate(std::vector<std::shared_ptr<Point2D>> points) {   
                
                if(points.size() < 3) return points;
                std::vector<std::shared_ptr<Point2D>> convexHull;
                std::sort(points.begin(), points.end(), compareSharedPoint2D);

                int n_points = points.size();
                convexHull.push_back(points[0]);
                convexHull.push_back(points[1]);
                convexHull = getSideConvexHull(points, convexHull, 2, n_points - 1) ;

                convexHull.push_back(points[n_points - 1]);
                convexHull.push_back(points[n_points - 2]);
                convexHull = getSideConvexHull(points, convexHull, n_points - 3, 0);

                return convexHull;
            }

            static std::vector<std::shared_ptr<Point2D>> getSideConvexHull(
                std::vector<std::shared_ptr<Point2D>> points,
                std::vector<std::shared_ptr<Point2D>> convexHull,
                int lower,
                int upper
            ) {
                int offset = lower > upper ? -1 : 1;
                for(int i = lower; i * offset <= upper; i+=offset) {
                    int convexHullSize = convexHull.size();
                
                    std::shared_ptr<Point2D> first = convexHull[convexHullSize - 2];
                    std::shared_ptr<Point2D> middle = convexHull[convexHullSize - 1];
                    std::shared_ptr<Point2D> last = points[i];
 
                    while(makeRightTurn(first, middle , last)) {
                        convexHull.pop_back();
                        convexHullSize = convexHull.size();
                        if(convexHullSize < 2) break;

                        first = convexHull[convexHullSize - 2];
                        middle = convexHull[convexHullSize - 1];  
                    }
                    convexHull.push_back(last);     
                }

                return convexHull;
            }

            static bool makeRightTurn( std::shared_ptr<Point2D> first, 
                                       std::shared_ptr<Point2D> middle, 
                                       std::shared_ptr<Point2D> last) {
                return (middle->y - first->y) * (last->x - middle->x) - (middle->x - first->x) * (last->y - middle->y) > 0;
            }
        };
        
        /***
         * Plane Sweep Algorithm is described in Chapter 2.1 of the book "Computational Geometry" by Mark de Berg
         **/
        class PlaneSweep{
            
            typedef struct {
                Point2D p;
                std::vector<Segment2D> segments;
            }event_t;        

            static void calculate(std::vector<std::shared_ptr<Segment2D>> segments) {
                
                std::set<Point2D, bool (*) (Point2D,Point2D)> event_queue(comparePoint2D);
                std::set<Segment2D, bool (*) (Segment2D,Segment2D)> status;

                for(std::shared_ptr<Segment2D> seg : segments) {
                    event_queue.insert(seg->start);
                    event_queue.insert(seg->end);
                }
                while(event_queue.size() > 0){
                    Point2D p = *event_queue.begin();
                    event_queue.erase(event_queue.begin());
                    //handleEventPoint(p, status);
                }
            }

            /***
             * L(p) = set of segments whose upper endpoint is p;
             * U(p) = set of segments whose lower endpoint is p;
             * C(p) = set of segments whose contains p;
             * ***/
            static void handleEventPoint(event_t event, std::set<Segment2D, bool (*) (Segment2D,Segment2D)> status) {
                std::vector<Segment2D> L_p;
                std::vector<Segment2D> U_p;
                std::vector<Segment2D> C_p;

                for(Segment2D seg : status) {
                    if(event.p == seg.start) L_p.push_back(seg);
                    if(event.p == seg.end) U_p.push_back(seg);

                }
                
                int siz = L_p.size() + U_p.size() + C_p.size();
            }

            static void findNewEvent(Segment2D sl, Segment2D sr, Point2D p)
            {

            }
        };
    };
};
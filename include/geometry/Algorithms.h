#pragma once
#include <geometry/Geometry.h>

#include <algorithm>
#include <iostream>
#include <memory>
#include <set>
#include <vector>
#include <queue>

namespace geometry {

    namespace algorithm {
        
        /***
         * MonotoneConvexHull is described in Chapter 1 in the book "Computational Geometry" by Mark de Berg
         **/
        class MonotoneConvexHull {
            public:
            
            static std::vector<std::shared_ptr<Point2D>> calculate(std::vector<std::shared_ptr<Point2D>> points) {   
                
                auto comparePoint2D = [] (std::shared_ptr<Point2D> p1, std::shared_ptr<Point2D>  p2) 
                    -> bool {return p1->x == p2->x ? p1->y < p2->y : p1->x < p2->x;};

                if(points.size() < 3) return points;
                std::vector<std::shared_ptr<Point2D>> convexHull;
                std::sort(points.begin(), points.end(), comparePoint2D);

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
                    while(convexHullSize > 1 && makeRightTurn(convexHull[convexHullSize - 2], convexHull[convexHullSize - 1] , points[i])) {
                        convexHull.pop_back();
                        convexHullSize = convexHull.size();
                    }
                    convexHull.push_back(points[i]);     
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

            public:

            class Event_Queue{
                public:
                std::set<Point2D> queue;
                std::map<Point2D, std::vector<Segment2D>> L;
                std::map<Point2D, std::vector<Segment2D>> U;
                std::map<Point2D, std::vector<Segment2D>> C;

                void addUpperPoint(Point2D p, Segment2D s) {
                    auto ptr = queue.find(p);
                    if(ptr == queue.end()){
                        queue.insert(p);
                    }

                    U[p].push_back(s);
                }

                void addLowerPoint(Point2D p, Segment2D s) {
                    auto ptr = queue.find(p);
                    if(ptr == queue.end()){
                        queue.insert(p);
                    }

                    L[p].push_back(s);
                }

                void addContainsPoint(Point2D p, Segment2D s1, Segment2D s2) {
                    auto ptr = queue.find(p);
                    if(ptr == queue.end()){
                        queue.insert(p);
                    }

                    C[p].push_back(s1);
                    C[p].push_back(s2);
                }

                Point2D pop() {
                    Point2D p = *(--queue.end());
                    queue.erase(--queue.end());
                    return p;
                }

                int getSize() const  {return queue.size();}
            };

            class Status_Tree {
                struct node{
                    Segment2D seg;
                    struct node* left;
                    struct node* right;
                };

                struct node* root;

                Status_Tree() {
                    root = NULL;
                }

                void insertStatus(Segment2D seg) {

                }

                void deleteStatus(Segment2D seg) {

                }

                void swapStatus(Segment2D seg) {

                }
            };


            static void calculate(std::vector<Segment2D> segments) {
                
                Event_Queue queue;

                for(Segment2D seg : segments) {
                    queue.addUpperPoint(seg.start, seg);
                    queue.addLowerPoint(seg.end, seg);
                }

                //queue.addContainsPoint()
                while(queue.getSize() > 0){
                    Point2D next = queue.pop();
                    handleEventPoint(next, &queue);
                }
            }

            static void handleEventPoint(Point2D event, Event_Queue* queue) {

            }

            static Point2D findNewEvent(Segment2D sl, Segment2D sr, Point2D p, Event_Queue* queue)
            {   
                Point2D intersectPoint = sl.intersectSegment2D(sl,sr);
                if(!intersectPoint.null_value && intersectPoint.y < p.y){
                    queue->addContainsPoint(intersectPoint,sl,sr);
                }
            }
        };
    };
};
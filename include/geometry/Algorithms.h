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

            std::vector<Point2D> points;
            std::vector<Point2D> convexHull;

            int step;
            int offset;
            bool running;

            MonotoneConvexHull() {}
            MonotoneConvexHull(std::vector<Point2D> newPoints) {
                resetPoints(points);
            }

            void resetPoints(std::vector<Point2D> newPoints) {
                step = 2;
                offset = 1;
                points = newPoints;
                auto comparePoint2D = [] (Point2D p1, Point2D p2) 
                    -> bool {return p1.x == p2.x ? p1.y < p2.y : p1.x < p2.x;};
                std::sort(points.begin(), points.end(), comparePoint2D);

                convexHull.clear();
                if(newPoints.size() < 3) {running = false; return;}
                convexHull.push_back(points[0]);
                convexHull.push_back(points[1]);
                running = true;
            }

            void calculate() {   
                int n_points = points.size();
                if(n_points< 3 || step < 0) {running = false; return;}


                int convexHullSize = convexHull.size();
                while(convexHullSize > 1 && makeRightTurn(convexHull[convexHullSize - 2], convexHull[convexHullSize - 1] , points[step])) {
                    convexHull.pop_back();
                    convexHullSize = convexHull.size();
                }
                convexHull.push_back(points[step]);   

                if(step + 1 >= n_points) {
                    convexHull.push_back(points[n_points - 1]);
                    convexHull.push_back(points[n_points - 2]);
                    offset = -1;
                    step = n_points - 2;
                } 
                step += offset;
            }

            static bool makeRightTurn( Point2D first, Point2D middle, Point2D last) {
                return (middle.y - first.y) * (last.x - middle.x) - (middle.x - first.x) * (last.y - middle.y) > 0;
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

                void addEventPoint(Point2D p) {
                    auto ptr = queue.find(p);
                    if(ptr == queue.end()){
                        queue.insert(p);
                    }
                }

                Point2D pop() {
                    Point2D p = *(queue.begin());
                    queue.erase(queue.begin());
                    return p;
                }

                int getSize() const  {return queue.size();}
            };

            class Status_Tree {
                public:
                struct node{
                    Segment2D seg;
                    struct node* left;
                    struct node* right;
                };

                std::vector<Segment2D> L;
                std::vector<Segment2D> U;
                std::vector<Segment2D> C;

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

            Point2D plane;
            Event_Queue queue;

            PlaneSweep(std::vector<Segment2D> segments) {
                for(Segment2D seg : segments) {
                    queue.addEventPoint(seg.start);
                    queue.addEventPoint(seg.end);
                }
            }

            void calculate() {  
                if(queue.getSize() > 0){
                    plane = queue.pop();
                    handleEventPoint(plane, &queue);
                }
            }

            static void handleEventPoint(Point2D event, Event_Queue* queue) {
                

            }

            static Point2D findNewEvent(Segment2D sl, Segment2D sr, Point2D p, Event_Queue* queue)
            {   
                Point2D intersectPoint = sl.intersectSegment2D(sl,sr);
                if(!intersectPoint.null_value && intersectPoint.y < p.y){
                    queue->addEventPoint(intersectPoint);
                }
            }
        };
    };
};
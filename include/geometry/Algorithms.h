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
            Point2D eventPoint;
            AVL<Point2D> queue;
            AVL<Segment2D> status;
            
            std::map<Point2D, std::vector<Segment2D>> U;
            std::map<Point2D, std::vector<Segment2D>> C;
            std::map<Point2D, std::vector<Segment2D>> L;
            std::vector<Point2D> intersectPoints;

            PlaneSweep(std::vector<Segment2D> segments) {
                init(segments);
            }

            void init(std::vector<Segment2D> segments) {
                intersectPoints.clear();
                U.clear();
                for(Segment2D seg : segments) {
                    queue.insertNode(seg.start);
                    U[seg.start].push_back(seg);

                    queue.insertNode(seg.end);
                    L[seg.end].push_back(seg);
                }
            }

            void calculate() {  
                if(queue.size() > 0){
                    eventPoint = queue.pop();
                    handleEventPoint(eventPoint);
                }

                //queue.printInOrder();
            }
            
            void handleEventPoint(Point2D event) {

                std::vector<Segment2D> neighbors;
                status.toArray(&neighbors);

                for(int i =  0; i < L[event].size(); i++) {
                    status.removeNode(L[event][i]);
                    std::cout << "Removing..." << std::endl;
                }

                for(int i = 0; i < C[event].size(); i++) {
                    status.removeNode(C[event][i]);

                    std::cout << "Reversing" << std::endl;
                    status.insertNode(C[event][i]);
                }

                for(int i =  0; i < U[event].size(); i++) {
                    status.insertNode(U[event][i]);
                    std::cout << "Inserting..." << std::endl;
                }

                neighbors.clear();
                status.toArray(&neighbors);
                int status_size = neighbors.size();

                if(U.size() + C.size() == 0) {
                    if(status_size < 2) return;

                    findNewEvent(neighbors[status_size / 2], neighbors[status_size / 2 + 1], event);
                } else {
                    
                }
                std::cout << "-------------------------" << std::endl;
                status.printInOrder();
            }

            Point2D findNewEvent(Segment2D sl, Segment2D sr, Point2D p) {   
                Point2D intersectPoint = sl.intersectSegment2D(sl,sr);

                std::cout << "INTERSECTION TEST: " << sl << " with " << sr << std::endl;
                if(!intersectPoint.null_value && intersectPoint.y > p.y){
                    queue.insertNode(intersectPoint);
                    intersectPoints.push_back(intersectPoint);
                    C[p].push_back(sl);
                    C[p].push_back(sr);
                }
            }
        };
    };
};
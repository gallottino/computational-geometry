#include <geometry/ConvexHull.hpp>


namespace geometry {
    MonotoneConvexHull::MonotoneConvexHull() {}

    MonotoneConvexHull::MonotoneConvexHull(std::vector<Point2D> newPoints) {
        resetPoints(points);
    }

    void MonotoneConvexHull::resetPoints(std::vector<Point2D> newPoints) {
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

    void MonotoneConvexHull::calculate() {   
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

    bool MonotoneConvexHull::makeRightTurn( Point2D first, Point2D middle, Point2D last) {
        return (middle.y - first.y) * (last.x - middle.x) - (middle.x - first.x) * (last.y - middle.y) > 0;
    }

};
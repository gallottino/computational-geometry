#include "Point.hpp"
#include <vector>
#include <queue>

namespace ComputationalGeometry
{
    class GrahamScan{

        std::vector<Point> set;
        std::queue<Point*> convexHull;

        GrahamScan(std::vector<Point> points) : set(points){}

        void init(){
            sort(set.begin(), set.end(), Point::comparePoint);
            convexHull.push(&set[0]);
            convexHull.push(&set[1]);
        }

    };
}
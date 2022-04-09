#include "Point.hpp"
#include <iostream>
#include <vector>
#include <stack>

namespace ComputationalGeometry
{
    class MonotoneConvexHull{
        public:
        int index;
        bool upper;
        std::vector<Point*> set;
        std::vector<Point*> convexHullUpper;
        std::vector<Point*> convexHullLower;

        MonotoneConvexHull(std::vector<Point*> points) : set(points){
            init();
        }

        void init(){
            upper = true;
            sort(set.begin(), set.end(), Point::comparePoint);
            convexHullUpper.push_back(set[0]);
            convexHullUpper.push_back(set[1]);
            index = 2;
        }

        void step(){
            if(index < 0) return;
            std::vector<Point*>* convexHull = upper ? &convexHullUpper : &convexHullLower;

            int size = convexHull->size();
            Point* last = set[index];
            Point* middle = (*convexHull)[size - 1];
            Point* first = (*convexHull)[size - 2];


            while(size > 1 && makeRightTurn(first, middle , last)){
                convexHull->pop_back();
                size = convexHull->size();
                middle = (*convexHull)[size - 1];
                first = (*convexHull)[size - 2];
            }
            convexHull->push_back(last);

            index =  upper ? index + 1 : index - 1;
            if(index == set.size()){
                upper = false;

                convexHullLower.push_back(set[index - 1]);
                convexHullLower.push_back(set[index - 2]);
                index -= 3;
            }
        }

        bool makeRightTurn(Point* first, Point* middle, Point* top){
            float m_1 = (middle->y - first->y) / (middle->x - first->x);
            float m_2 = (top->y - middle->y) / (top->x - middle->x);
            return m_2 < m_1;
        }

    };
}
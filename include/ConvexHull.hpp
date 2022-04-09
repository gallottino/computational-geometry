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

        MonotoneConvexHull(){
            index = -1;
        }

        void init(){
            resetConvexHull();

            sort(set.begin(), set.end(), Point::comparePoint);
            convexHullUpper.push_back(set[0]);
            convexHullUpper.push_back(set[1]);
            index = 2;
        }

        void resetConvexHull() {
            index = -1;
            upper = true;
            convexHullLower.clear();
            convexHullUpper.clear();
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

        bool makeRightTurn(Point* first, Point* middle, Point* top) {
            return (middle->y - first->y) * (top->x - middle->x) - (middle->x - first->x) * (top->y - middle->y) > 0;
        }

        void render(sf::RenderWindow& window) {
            for(int i = 1; i < convexHullUpper.size(); i++) {
                sf::Vertex line[2];
                line[0] = convexHullUpper[i]->getCenter();
                line[1] = convexHullUpper[i - 1]->getCenter();
                line[0].color = sf::Color::Black;
                line[1].color = sf::Color::Black;

                window.draw(line, 2, sf::Lines);
            }
            for(int i = 1; i < convexHullLower.size(); i++) {
                sf::Vertex line[2];
                line[0] = convexHullLower[i]->getCenter();
                line[1] = convexHullLower[i - 1]->getCenter();
                
                line[0].color = sf::Color::Black;
                line[1].color = sf::Color::Black;
                window.draw(line, 2, sf::Lines);
            }

            for(int i = 0; i < set.size(); i++) {
                set[i]->render(window);
            }
        }
    };
}
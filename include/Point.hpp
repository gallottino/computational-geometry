#include "SFML/Graphics.hpp"

namespace ComputationalGeometry{

    class Point{
    public:
        float x;
        float y;
        sf::CircleShape* shape;

        Point(float x, float y){
            this->x = x;
            this->y = y;
            shape = new sf::CircleShape(5.0f);
            shape->setFillColor(sf::Color::Red);
            shape->move(x,y);
        }

        void render(sf::RenderWindow& window) const {
            window.draw(*shape);      
        }

        void setConvexHull(){
            shape->setFillColor(sf::Color::Green);
        }

        void setInternal(){
            shape->setFillColor(sf::Color::Blue);
        }

        static bool comparePoint(Point p1, Point p2){
            return p1.x == p2.x ? p1.y < p2.y : p1.x < p2.x;
        }
    };



    static bool makeRightTurn(Point p1, Point p2, Point p3){
        return p1.y < p2.y && p2.y > p3.y;  
    }

    static void convexHullGrahamScan(std::vector<Point> points){
        
    }

};
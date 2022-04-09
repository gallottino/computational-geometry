#ifndef POINT_H_
#define POINT_H_

#include "SFML/Graphics.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

namespace ComputationalGeometry{

    class Point{
    public:
        float x;
        float y;
        float radius;

        sf::CircleShape* shape;

        Point(float x, float y, float radius){
            this->x = x;
            this->y = y;
            this->radius = radius;

            shape = new sf::CircleShape(radius * 2);
            shape->setFillColor(sf::Color(rand()%256, rand()%256, rand()%256));
            shape->setOutlineColor(sf::Color::Black);
            shape->setOutlineThickness(1.f);
            shape->move(x - 2 * radius,y - 2 * radius);
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

        sf::Vector2f getCenter(){
            return sf::Vector2f(x, y);
        }

        static bool comparePoint(Point* p1, Point* p2){
            return p1->x == p2->x ? p1->y < p2->y : p1->x < p2->x;
        }

        static std::vector<Point> loadPoints(const char* filename)
        {
            std::vector<Point> points;
            std::ifstream file_in(filename);

            std::string line;
            while(std::getline(file_in, line))
            {
                std::stringstream iss(line);
                float x, y;
                if (!(iss >> x >> y)) { break; } 

                points.push_back(Point(x,y,2.5f));
            }

            return points;
        }
    };
};

#endif
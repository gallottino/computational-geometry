#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream> 

#include <time.h>

class Point
{
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

    void render(sf::RenderWindow& window) const
    {
        window.draw(*shape);
        
    }

    void setConvexHull(){
        shape->setFillColor(sf::Color::Green);

    }

    void setInternal()
    {
        shape->setFillColor(sf::Color::Blue);
    }
};

bool comparePoint(Point p1, Point p2)
{
    return p1.x == p2.x ? p1.y < p2.y : p1.x < p2.x;
}

bool makeRightTurn(Point* p1, Point* p2, Point* p3)
{
    return p1->y < p2->y && p2->y > p3->y;
}

std::vector<Point> loadPoints(const char* filename)
{
    std::vector<Point> points;

    std::ifstream file_in(filename);

    std::string line;
    while(std::getline(file_in, line))
    {
        std::stringstream iss(line);
        float x, y;
        if (!(iss >> x >> y)) { break; } 

        points.push_back(Point(x,y));
    }

    return points;
}

int main()
{

    std::vector<Point> points = loadPoints("../points.txt");

    std::vector<Point*> convexHull;
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    srand (time(NULL));

    int index = 2;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i position = sf::Mouse::getPosition(window);
                points.push_back(Point(position.x,position.y));
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                sort(points.begin(), points.end(), comparePoint);
                points[0].setConvexHull();
                points[1].setConvexHull();
                convexHull.push_back(&points[0]);
                convexHull.push_back(&points[1]);
            }


        }

        window.clear();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
        {   
            int i = index;
            points[i].setConvexHull();
            convexHull.push_back(&points[i]);

            while(convexHull.size() > 2 && makeRightTurn(convexHull[convexHull.size() - 1], convexHull[convexHull.size() - 2], convexHull[convexHull.size() - 3]) ){
                convexHull[convexHull.size()  - 2]->setInternal();
                convexHull.erase(convexHull.begin() + convexHull.size()  - 2);
            }
            index++;
            std::cout << index  << std::endl;
        }
        for(int i = 0; i < points.size(); i++)
        {
            points[i].render(window);
        }

        window.display();
    }

    return 0;
}
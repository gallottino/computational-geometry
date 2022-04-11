#include <SFML/Graphics.hpp>

#include <geometry/Geometry.h>
#include <geometry/Algorithms.h>
#include <memory>
#include <vector>

using namespace geometry;

#define GRID_DIM 40.f

void drawGrid(sf::RenderWindow& window)
{
    for(int i = 0; i < 20; i++)
    {
        sf::Vertex line[2];
        line[0] = sf::Vertex(sf::Vector2f((float) i * GRID_DIM, 0.f));
        line[1] = sf::Vertex(sf::Vector2f((float) i * GRID_DIM, 800.f));
        line[0].color = sf::Color(200.f,200.f,200.f);
        line[1].color = sf::Color(200.f,200.f,200.f);

        window.draw(line, 2, sf::Lines);

        line[0] = sf::Vertex(sf::Vector2f(0.f, (float) i * GRID_DIM));
        line[1] = sf::Vertex(sf::Vector2f(800.f,(float) i * GRID_DIM));
        line[0].color = sf::Color(200.f,200.f,200.f);
        line[1].color = sf::Color(200.f,200.f,200.f);
        window.draw(line, 2, sf::Lines);
    }
}


void drawPoints(sf::RenderWindow& window, std::vector<std::shared_ptr<Point2D>> points)
{   
    float radius = 2.f;

    for(std::shared_ptr<Point2D> p : points)
    {
        sf::CircleShape shape;
        shape.setRadius(radius);
        shape.setFillColor(sf::Color::Black);
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(1.f);
        shape.move(p->x - 2 * radius,p->y - 2 * radius);
        window.draw(shape);
    }
}

void drawConvexHull(sf::RenderWindow& window, std::vector<std::shared_ptr<Point2D>> convexHull)
{
    for(int i = 1; i < convexHull.size(); i++) {
        sf::Vertex line[2];

        line[0] = sf::Vertex(sf::Vector2f(convexHull[i]->x, convexHull[i]->y));
        line[0].color = sf::Color::Black;

        line[1] = sf::Vertex(sf::Vector2f(convexHull[i  - 1]->x, convexHull[i - 1]->y));
        line[1].color = sf::Color::Black;

        window.draw(line, 2, sf::Lines);
    }
}

int main()
{   
    std::vector<std::shared_ptr<Point2D>> convexHull;
    std::vector<std::shared_ptr<Point2D>> points;
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                
                case sf::Event::MouseButtonPressed:
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        sf::Vector2i position = sf::Mouse::getPosition(window);
                        points.push_back(std::make_shared<Point2D>(Point2D(position.x,position.y)));
                    }
                    break;

                case sf::Event::KeyReleased:
                    if(event.key.code == sf::Keyboard::S){
                        convexHull.clear();
                        convexHull = geometry::algorithm::MonotoneConvexHull::calculate(points);
                    }
            }
        }


        window.clear(sf::Color::White);
        drawGrid(window);
        drawPoints(window, points);
        drawConvexHull(window, convexHull);
        window.display();
    }

    return 0;
}
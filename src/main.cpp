#include <SFML/Graphics.hpp>
#include "Point.hpp"
#include "ConvexHull.hpp"

using namespace ComputationalGeometry;

int main()
{
    std::vector<Point*> points;
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

    float ms_step = 100.0f;
    
    sf::Clock clock;
    MonotoneConvexHull* algo = NULL;
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
                        points.push_back(new Point(position.x,position.y, 2.5f));
                    }
                    break;
                
                case sf::Event::KeyReleased:
                    if(event.key.code == sf::Keyboard::S)
                    {
                        algo = new MonotoneConvexHull(points);
                    }
            }

        }

        if(algo != NULL && clock.getElapsedTime().asMilliseconds()> ms_step)
        {
            algo->step();
            clock.restart();
        }

        window.clear(sf::Color::White);

        if(algo != NULL){
            for(int i = 1; i < algo->convexHullUpper.size(); i++) {
                sf::Vertex line[2];
                line[0] = algo->convexHullUpper[i]->getCenter();
                line[1] = algo->convexHullUpper[i - 1]->getCenter();
                line[0].color = sf::Color::Black;
                line[1].color = sf::Color::Black;

                window.draw(line, 2, sf::Lines);
            }
            for(int i = 1; i < algo->convexHullLower.size(); i++) {
                sf::Vertex line[2];
                line[0] = algo->convexHullLower[i]->getCenter();
                line[1] = algo->convexHullLower[i - 1]->getCenter();
                
                
                line[0].color = sf::Color::Black;
                line[1].color = sf::Color::Black;
                window.draw(line, 2, sf::Lines);
            }
        }
        for(int i = 0; i < points.size(); i++) {
            points[i]->render(window);
        }


        window.display();
    }

    return 0;
}
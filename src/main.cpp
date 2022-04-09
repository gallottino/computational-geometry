#include <SFML/Graphics.hpp>
#include "Point.hpp"
#include "ConvexHull.hpp"

using namespace ComputationalGeometry;

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


int main()
{
    std::vector<Point*> points;
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    
    float ms_step = 100.0f;
    sf::Clock clock;
    MonotoneConvexHull algo;
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
                        algo.set.push_back(new Point(position.x,position.y, 1.f));
                    }
                    break;
                
                case sf::Event::KeyReleased:
                    if(event.key.code == sf::Keyboard::S)
                    {
                        algo.init();
                    }
                    
                    if(event.key.code == sf::Keyboard::R)
                    {
                        algo.resetConvexHull();
                    }
            }
        }

        if(clock.getElapsedTime().asMilliseconds()> ms_step)
        {
            algo.step();
            clock.restart();
        }

        window.clear(sf::Color::White);
        drawGrid(window);
        algo.render(window);

        window.display();
    }

    return 0;
}
#include <SFML/Graphics.hpp>
#include <data_structures/avl.hpp>

#include <geometry/Algorithms.h>
#include <geometry/Geometry.h>
#include <geometry/Utilities.h>
#include <memory>
#include <vector>

using namespace geometry;

#define GRID_DIM 20.f
#define GRID_HEIGHT 600.f
#define GRID_WIDTH 600.f

void drawGrid(sf::RenderWindow& window)
{
    for(int i = 0; i * GRID_DIM <= GRID_HEIGHT; i++)
    {
        sf::Vertex line[2];
        line[0] = sf::Vertex(sf::Vector2f((float) i * GRID_DIM, 0.f));
        line[1] = sf::Vertex(sf::Vector2f((float) i * GRID_DIM, GRID_HEIGHT));
        line[0].color = sf::Color(200.f,200.f,200.f);
        line[1].color = sf::Color(200.f,200.f,200.f);

        window.draw(line, 2, sf::Lines);

        line[0] = sf::Vertex(sf::Vector2f(0.f, (float) i * GRID_DIM));
        line[1] = sf::Vertex(sf::Vector2f(GRID_HEIGHT,(float) i * GRID_DIM));
        line[0].color = sf::Color(200.f,200.f,200.f);
        line[1].color = sf::Color(200.f,200.f,200.f);
        window.draw(line, 2, sf::Lines);
    }
}

void drawPoint(sf::RenderWindow& window, Point2D p, sf::Color color){
    float radius = 3.f;

    if(p.null_value) return;

    sf::CircleShape shape;
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setOutlineColor(color);
    shape.setOutlineThickness(1.f);
    shape.move(p.x - radius,p.y - radius);
    window.draw(shape);
}

void drawOutlinePoint(sf::RenderWindow& window, Point2D p, sf::Color color){
    float radius = 5.f;

    if(p.null_value) return;

    sf::CircleShape shape;
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(color);
    shape.setOutlineThickness(2.f);
    shape.move(p.x - radius,p.y - radius);
    window.draw(shape);
}


void drawHorizontalLine(sf::RenderWindow& window, Point2D point) {
    sf::Vertex line[2];
    line[0] = sf::Vertex(sf::Vector2f(0.f, point.y));
    line[1] = sf::Vertex(sf::Vector2f(GRID_WIDTH, point.y));
    line[0].color = sf::Color::Black;
    line[1].color = sf::Color::Black;

    window.draw(line, 2, sf::Lines);
}

void drawPoints(sf::RenderWindow& window, std::vector<Point2D> points)
{   

    for(Point2D p : points)
    {
        drawPoint(window,p, sf::Color::Black);
    }
}

void drawSegment2D(sf::RenderWindow& window, Point2D start, Point2D end) {
        sf::Vertex line[2];

        line[0] = sf::Vertex(sf::Vector2f(start.x, start.y));
        line[0].color = sf::Color::Black;

        line[1] = sf::Vertex(sf::Vector2f(end.x, end.y));
        line[1].color = sf::Color::Black;

        window.draw(line,2,sf::Lines);
        drawOutlinePoint(window, start, sf::Color::Red);
        drawOutlinePoint(window, end, sf::Color::Red);
}

void drawConvexHull(sf::RenderWindow& window, std::vector<Point2D> convexHull)
{
    for(int i = 1; i < convexHull.size(); i++) {

        drawSegment2D(window, convexHull[i - 1], convexHull[i]);
    }
}

void drawSegments2D(sf::RenderWindow& window, std::vector<Segment2D> segments) {
    for(Segment2D seg : segments) {
        drawSegment2D(window, seg.start, seg.end);
    }
}

void drawSegment2DCollision(sf::RenderWindow& window, std::vector<Segment2D> segments) {
    
    drawPoint(window, segments[0].intersectSegment2D(segments[0],segments[1]), sf::Color::Blue);
}

int main() {   
    std::vector<Point2D> points;
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    
    AVL<int> status;
    status.insertNode(1);
    status.insertNode(10);
    status.insertNode(40);
    status.insertNode(15);
    status.insertNode(2);
    status.insertNode(7);
    status.insertNode(12);
    status.insertNode(4);
    status.insertNode(24);
    status.insertNode(13);

    status.removeNode(12);

    status.printLeftOrder();

    std::vector<Segment2D> segments = randomVectorSegment2D(10);
    geometry::algorithm::PlaneSweep planeSweep(segments);
    geometry::algorithm::MonotoneConvexHull convexHullAlgo;
    sf::Clock clock;
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
                    points.push_back(Point2D(position.x,position.y));
                }
                break;

                case::sf::Event::KeyPressed:
                    
                    if(event.key.code == sf::Keyboard::S){
                        convexHullAlgo.resetPoints(points);
                    }
                    if(event.key.code == sf::Keyboard::R) {
                        segments = randomVectorSegment2D(10);
                    }
                break;
            }
        }

        window.clear(sf::Color::White);
        drawGrid(window);
        drawPoints(window, points);

        drawConvexHull(window, convexHullAlgo.convexHull);
        
        if(clock.getElapsedTime().asMilliseconds() > 100) {
            convexHullAlgo.calculate();
            clock.restart();
        }

        drawSegments2D(window,segments);
        drawHorizontalLine(window,planeSweep.plane);
        if(clock.getElapsedTime().asMilliseconds() > 500) {
           planeSweep.calculate();
            clock.restart();
        }


        window.display();
    }

    return 0;
}
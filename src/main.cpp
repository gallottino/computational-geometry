#include <SFML/Graphics.hpp>

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
    float radius = 2.5f;

    if(p.null_value) return;

    sf::CircleShape shape;
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setOutlineColor(color);
    shape.setOutlineThickness(1.f);
    shape.move(p.x - radius,p.y - radius);
    window.draw(shape);
}

void drawPoints(sf::RenderWindow& window, std::vector<std::shared_ptr<Point2D>> points)
{   
    float radius = 2.f;

    for(std::shared_ptr<Point2D> p : points)
    {
        drawPoint(window,*p, sf::Color::Black);
    }
}

void drawSegment2D(sf::RenderWindow& window, Point2D start, Point2D end) {
        sf::Vertex line[2];

        line[0] = sf::Vertex(sf::Vector2f(start.x, start.y));
        line[0].color = sf::Color::Black;

        line[1] = sf::Vertex(sf::Vector2f(end.x, end.y));
        line[1].color = sf::Color::Black;

        window.draw(line,2,sf::Lines);
        drawPoint(window, start, sf::Color::Red);
        drawPoint(window, end, sf::Color::Red);
}

void drawConvexHull(sf::RenderWindow& window, std::vector<std::shared_ptr<Point2D>> convexHull)
{
    for(int i = 1; i < convexHull.size(); i++) {

        drawSegment2D(window, *(convexHull[i - 1]), *(convexHull[i]));
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

int main()
{   
    std::vector<std::shared_ptr<Point2D>> convexHull;
    std::vector<std::shared_ptr<Point2D>> points;
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    

    std::vector<Segment2D> segments = randomVectorSegment2D(2);

    geometry::algorithm::PlaneSweep::calculate(segments);

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

                case::sf::Event::KeyPressed:
                    
                    if(event.key.code == sf::Keyboard::S){
                        convexHull.clear();
                        convexHull = geometry::algorithm::MonotoneConvexHull::calculate(points);
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
        drawSegments2D(window,segments);
        drawConvexHull(window, convexHull);
        drawSegment2DCollision(window,segments);
        window.display();
    }

    return 0;
}
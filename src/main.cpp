#include <SFML/Graphics.hpp>
#include <data_structures/avl.hpp>


#include <geometry/Geometry.hpp>
#include <geometry/ConvexHull.hpp>
#include <geometry/PlaneSweep.hpp>
#include <geometry/Utilities.hpp>

#include <ui/Button.hpp>
#include <ui/GeometryGrid.hpp>
#include <ui/Label.hpp>

#include <memory>
#include <vector>

using namespace geometry;

#define GRID_DIM 20.f
#define GRID_HEIGHT 600.f
#define GRID_WIDTH 600.f


void drawPoint(sf::RenderWindow& window, Point2D p, sf::Color color) {
    float radius = 1.5f;

    if(p.null_value) return;

    sf::CircleShape shape;
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setOutlineColor(color);
    shape.setOutlineThickness(1.f);
    shape.move(p.x - radius,p.y - radius);
    window.draw(shape);
}

void drawOutlinePoint(sf::RenderWindow& window, Point2D p, sf::Color color) {
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


void drawHorizontalLine(sf::RenderWindow& window, Point2D point) {
    sf::Vertex line[2];
    line[0] = sf::Vertex(sf::Vector2f(0.f, point.y));
    line[1] = sf::Vertex(sf::Vector2f(GRID_WIDTH, point.y));
    line[0].color = sf::Color::Black;
    line[1].color = sf::Color::Black;

    window.draw(line, 2, sf::Lines);
}

void drawPoints(sf::RenderWindow& window, std::vector<Point2D> points, sf::Color color) {   

    for(Point2D p : points) {
        drawPoint(window,p, color);
    }
}

void drawSegment2D(sf::RenderWindow& window, Point2D start, Point2D end) {
        sf::Vertex line[2];

        line[0] = sf::Vertex(sf::Vector2f(start.x, start.y));
        line[0].color = sf::Color::Black;

        line[1] = sf::Vertex(sf::Vector2f(end.x, end.y));
        line[1].color = sf::Color::Black;

        window.draw(line,2,sf::Lines);
        drawOutlinePoint(window, start, sf::Color::Blue);
        drawOutlinePoint(window, end, sf::Color::Blue);
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

void drawPolygon(sf::RenderWindow& window, std::vector<Point2D> points) {
    
    sf::Vertex line[2];
    for(int i = 1; i < points.size(); i++) {
        
        line[0] = sf::Vertex(sf::Vector2f(points[i - 1].x, points[i - 1].y));
        line[1] = sf::Vertex(sf::Vector2f(points[i].x, points[i].y));
        line[0].color = sf::Color::Black;
        line[1].color = sf::Color::Black;

        window.draw(line, 2, sf::Lines);
    }

    if(points.size() < 3) return;
    line[0] = sf::Vertex(sf::Vector2f(points[0].x, points[0].y));
    line[1] = sf::Vertex(sf::Vector2f(points[points.size() - 1].x, points[points.size() - 1].y));
    line[0].color = sf::Color::Black;
    line[1].color = sf::Color::Black;
    window.draw(line, 2, sf::Lines);
}

int main() {   
    std::vector<Point2D> points;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Galmetry Sandobx");

    std::vector<Segment2D> segments = loadSegment2DFromFile("verify.txt");
    geometry::PlaneSweep planeSweep(segments);
    geometry::MonotoneConvexHull convexHullAlgo;
    

    ui::GeometryGrid grid(sf::Vector2f(25.f,25.f), sf::Vector2f(500.f,500.f));

    ui::Button b("Convex Hull", sf::Vector2f(550.f,25.f), sf::Vector2f(190,50.f));
    b.onClick = [&] () {
        planeSweep.calculate();
    };

    ui::Button b2("Plane Sweep", sf::Vector2f(550.f,52+ 25.f), sf::Vector2f(190,50));
    b.onClick = [&] () {
        planeSweep.calculate();
    };

    ui::Label description("Galmetry Sandobx 2022", sf::Vector2f(25.f,5.f));

    geometry::Polygon2D polygon = randomPolygon2D(10, 100.f, 300.f);

    geometry::Point2D p;
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {   
            b.update(event,window);
            switch(event.type)
            {
                case sf::Event::Closed:
                window.close();
                break;
            

                case::sf::Event::KeyPressed:
                    
                    if(event.key.code == sf::Keyboard::S) {
                        convexHullAlgo.resetPoints(points);
                    }

                    if(event.key.code == sf::Keyboard::R) {
                        segments = randomVectorSegment2D(50, 0, GRID_WIDTH);
                        planeSweep.init(segments);
                        points.clear();
                    }

                    if(event.key.code == sf::Keyboard::Enter) {
                        polygon.vertices.clear(); 
                        
                    }
                    
                break;
            }
            
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                auto posMouse = sf::Mouse::getPosition(window);
                points.push_back(Point2D(posMouse.x, posMouse.y));
                std::cout << "inserted Points" << std::endl;
            }

        }

        window.clear(sf::Color::White);
        
        grid.render(window);

        drawPolygon(window,points);
        //drawPoints(window, points, sf::Color::Black);
        //drawConvexHull(window, convexHullAlgo.convexHull);
        //drawSegments2D(window,segments);

        ///drawPoints(window, planeSweep.intersectPoints, sf::Color::Red);
        //planeSweep.drawIntersectionPoints(window);
        //drawHorizontalLine(window,planeSweep.eventPoint);
        //b.render(window);
        //b2.render(window);
        description.render(window);
        window.display();
    }

    return 0;
}
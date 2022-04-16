#pragma once

#include <SFML/Graphics.hpp>
#include <geometry/Geometry.h>
#include <functional>

/*** 
 * This class is usefull to draw with SFML Libraries al the stuff related to the package geometry
 ***/
class Renderer {

    public:
    Renderer(std::string title, int width, int height);

    //This method is overload with every geometry entity in the geometry library
    void render(geometry::Point2D point);
    void render(geometry::Point2D point, sf::Color color, float radius);
    void render(geometry::Segment2D segment);

    void clear();
    bool isOpen();
    void pollEvent(std::function<void(sf::Event)> eventManager);

    private:
    sf::RenderWindow* _window;
    int _screen_width, _screen_height;
};
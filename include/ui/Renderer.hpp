#pragma once

#include <SFML/Graphics.hpp>
#include <geometry/Geometry.hpp>
#include <functional>

/*** 
 * This class is usefull to draw with SFML Libraries al the stuff related to the package geometry
 ***/
class Renderer {

    public:
    //This method is overload with every geometry entity in the geometry library
    static void render(geometry::Point2D point);
    static void render(geometry::Point2D point, sf::Color color, float radius);
    static void render(geometry::Segment2D segment);
};
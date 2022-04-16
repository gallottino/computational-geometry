#pragma once
#include <SFML/Graphics.hpp>

namespace ui {
        namespace Color {
            static const sf::Color Grey = sf::Color(200.f,200.f,200.f);
        }
};

class RenderObject {
    
    public:
    virtual void update(sf::Event event, sf::RenderWindow& window) = 0;
    virtual void render(sf::RenderWindow& window) = 0;

    protected:
    sf::Vector2f _pos;
    sf::Vector2f _size;
};
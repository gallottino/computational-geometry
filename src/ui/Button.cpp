#include "ui/Button.hpp"

#include <iostream>
namespace ui {
    Button::Button(std::string title, sf::Vector2f pos, sf::Vector2f size) {
        this->title = title;
        this->_pos = pos;
        this->_size = size;
    }

    void Button::update(sf::Event event, sf::RenderWindow& window) {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i posMouse = sf::Mouse::getPosition(window);
            if( posMouse.x > _pos.x && 
                posMouse.y > _pos.y &&
                posMouse.x < _pos.x + _size.x &&
                posMouse.y < _pos.y + _size.y) { 
                    onClick();
            }
        }
    }

    void Button::render(sf::RenderWindow& window) {
        sf::RectangleShape box;
        sf::Text text;

        sf::Color defaultColor = sf::Color::Blue;

        static sf::Font font;
        font.loadFromFile("../res/elephant.ttf");

        box.setFillColor(sf::Color::Transparent);
        box.setOutlineColor(defaultColor);
        box.setOutlineThickness(2);
        box.setSize(_size);
        box.move(_pos + sf::Vector2f(2,2));

        text.setFont(font);
        text.setString(title);
        text.setCharacterSize(15);
        text.setFillColor(defaultColor);

        auto textBounds = text.getLocalBounds();
        text.move(sf::Vector2f( _pos.x + ( _size.x - textBounds.width) / 2,
                                _pos.y + ( _size.y - textBounds.height) / 2));

        window.draw(box);
        window.draw(text);
    }
}
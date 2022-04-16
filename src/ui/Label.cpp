#include <ui/Label.hpp>

namespace ui {
    
    Label::Label(std::string label, sf::Vector2f pos) {
        _charSize = 15;
        _label = label;
        _pos = pos;
    }

    Label::Label(std::string label, sf::Vector2f pos, int charSize) {
        _pos = pos;
        _label = label;
        _charSize = charSize;
    }

    void Label::render(sf::RenderWindow& window) {
        sf::Text text;

        static sf::Font font;
        font.loadFromFile("../res/elephant.ttf");

        text.setFont(font);
        text.setCharacterSize(_charSize);
        text.setFillColor(sf::Color::Black);
        text.setString(_label);
        text.move(_pos);

        window.draw(text);
    }

    void Label::update(sf::Event event, sf::RenderWindow& window) {}

    void Label::setText(std::string label) {

    }

}
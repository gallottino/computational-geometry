#pragma once

#include <string>
#include <ui/RenderObject.hpp>
#include <SFML/Graphics.hpp>

namespace ui {
    
    class Label : RenderObject {
        public:
        Label(std::string label, sf::Vector2f pos);
        Label(std::string label, sf::Vector2f pos, int charSize);

        void render(sf::RenderWindow& window);
        void update(sf::Event event, sf::RenderWindow& window);

        void setText(std::string label);

        private:
        int _charSize;
        std::string _label;
    };
}
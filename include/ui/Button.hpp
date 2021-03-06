#pragma once
#include <functional>
#include <string>

#include <ui/RenderObject.hpp>

namespace ui {
    class Button : RenderObject {

        public:
        Button(std::string title, sf::Vector2f pos, sf::Vector2f size);

        void render(sf::RenderWindow& window);
        void update(sf::Event event, sf::RenderWindow& window);

        std::function<void()> onClick;

        private:
        std::string title;
        sf::Color backgroundColor;
        sf::Color outlineColor;
        sf::Color textColor;
    };
}
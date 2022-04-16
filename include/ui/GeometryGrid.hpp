#pragma once

#include <geometry/Geometry.hpp>
#include <ui/RenderObject.hpp>

namespace ui {
    
    class GeometryGrid : RenderObject {
        public:
        GeometryGrid(sf::Vector2f pos, sf::Vector2f size);

        void render(sf::RenderWindow& window);
        void update(sf::Event event, sf::RenderWindow& window);
        void clear();

        private:
        std::vector<RenderObject> _renderObjects;
    };
}
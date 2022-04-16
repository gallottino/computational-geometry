#include <ui/GeometryGrid.hpp>
#include <ui/Renderer.hpp>
#define GRID_DIM 20

namespace ui {
    
    GeometryGrid::GeometryGrid(sf::Vector2f pos, sf::Vector2f size) {
        _pos = pos;
        _size = size;   
    }

    void GeometryGrid::render(sf::RenderWindow& window) {

        for(int i = 0; i * GRID_DIM <= _size.y; i++) {
            sf::Vertex line[2];
            line[0] = sf::Vertex(sf::Vector2f((float) i * GRID_DIM + _pos.x, _pos.y));
            line[1] = sf::Vertex(sf::Vector2f((float) i * GRID_DIM + _pos.x, _pos.y + _size.y));
            line[0].color = ui::Color::Grey;
            line[1].color = ui::Color::Grey;
            window.draw(line, 2, sf::Lines);

            line[0] = sf::Vertex(sf::Vector2f(_pos.x, (float) i * GRID_DIM + _pos.y));
            line[1] = sf::Vertex(sf::Vector2f(_pos.x + _size.x,(float) i * GRID_DIM + _pos.y));
            line[0].color = ui::Color::Grey;
            line[1].color = ui::Color::Grey;
            window.draw(line, 2, sf::Lines);
        }
    }

    void GeometryGrid::update(sf::Event evvent, sf::RenderWindow& window) {
        
    }
}
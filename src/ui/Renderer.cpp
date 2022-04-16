#include <ui/Renderer.hpp>

Renderer::Renderer(std::string title, int width, int height) {
    _screen_width = width;
    _screen_height = height;
    _window = new sf::RenderWindow(sf::VideoMode(width, height), title);
}

void Renderer::clear() {
    _window->clear();
}

void Renderer::render(geometry::Point2D point) {
    float radius = 2.5f;

    if(point.null_value) return;

    sf::CircleShape shape;
    shape.setRadius(1.f);
    shape.move(point.x - radius, _screen_height - point.y + radius);
    _window->draw(shape);
}

bool Renderer::isOpen() {
    return _window->isOpen();
}

void Renderer::pollEvent(std::function<void(sf::Event)> eventManager) {

    sf::Event event;
    while(_window->pollEvent(event)){
        eventManager(event);
    }
}
#include <SFML/Graphics.hpp>

class RenderObject {
    
    public:
    virtual void update(sf::Event event, sf::RenderWindow& window) = 0;
    virtual void render(sf::RenderWindow& window) = 0;

    protected:
    sf::Vector2f _pos;
    sf::Vector2f _size;
};
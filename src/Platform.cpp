#include "Platform.hpp"

Platform::Platform(sf::Vector2f size, sf::Vector2f position) {
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Green);
}

void Platform::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Platform::getBounds() const {
    return shape.getGlobalBounds();
}

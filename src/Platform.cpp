#include "Platform.hpp"
#include <iostream>
Platform::Platform(sf::Vector2f size, sf::Vector2f position) {
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::White);
}

void Platform::draw(sf::RenderWindow& window) {
    sf::Texture tiles;
    //texture MUST be in the same function as window.draw, otherwise the texture lifespan expires and is not drawn. Issues are due to contrainerization... see docs
    if (!tiles.loadFromFile("tiles.png", false, sf::IntRect({0, 0}, {240, 288})))
    {
        std::cout << "TEXTURE NOT FOUND" << std::endl;    
    }
    shape.setTexture(&tiles); // texture is a sf::Texture
    shape.setTextureRect(sf::IntRect({16, 16}, {64, 64}));

    window.draw(shape);
}
sf::FloatRect Platform::getBounds() const {
    return shape.getGlobalBounds();
}

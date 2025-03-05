#include "Platform.hpp"
#include <iostream>
Platform::Platform(sf::Vector2f size, sf::Vector2f position) {
    
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::White);
}

void Platform::draw(sf::RenderWindow& window) {
    sf::Texture tiles;
    tiles.setRepeated(true);

    //texture MUST be in the same function as window.draw, otherwise the texture lifespan expires and is not drawn. Issues are due to contrainerization... see docs
    if (!tiles.loadFromFile("textures/platform1.png", false))
    {
        std::cout << "TEXTURE NOT FOUND -tiles" << std::endl;    
    }
    shape.setTextureRect({{0, 0}, {288, 96}});
    shape.setTexture(&tiles); // texture is a sf::Texture
    window.draw(shape);
}
sf::FloatRect Platform::getBounds() const {
    return shape.getGlobalBounds();
}

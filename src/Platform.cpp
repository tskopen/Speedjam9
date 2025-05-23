#include "Platform.hpp"
#include <iostream>
#include <string>

Platform::Platform(sf::Vector2f size, sf::Vector2f position, PlatformType platformType) : type(platformType) {
    shape.setSize(size);
    shape.setPosition(position);
    if (type == PlatformType::Bouncy)
    {
        shape.setFillColor(sf::Color::Red);
    }
    else if (type == PlatformType::Slippery)
    {
        shape.setFillColor(sf::Color::Yellow);
    } 
    else
    {
        shape.setFillColor(sf::Color::White);

    }
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

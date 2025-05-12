#pragma once
#include <SFML/Graphics.hpp>
#include <string>
enum class PlatformType {
    Standard,
    Bouncy,
    Slippery
};
class Platform {
public:
    Platform(sf::Vector2f size, sf::Vector2f position, PlatformType platformType);
    PlatformType type;
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;


private:
    sf::RectangleShape shape;
};

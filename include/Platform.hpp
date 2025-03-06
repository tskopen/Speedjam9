#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Platform {
public:
    Platform(sf::Vector2f size, sf::Vector2f position, std::string platformtype);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    std::string getplatformtype() const {
        return platformtype;
    };

private:
    sf::RectangleShape shape;
    std::string platformtype;
};

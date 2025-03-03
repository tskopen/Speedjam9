#pragma once
#include <SFML/Graphics.hpp>

class JumpAnimation {
private:
    sf::Sprite character;
    sf::Texture texture;
    sf::Clock clock;
    sf::RenderWindow& window;

public:
    JumpAnimation(sf::RenderWindow& window);
    void update();
    void draw();
};
#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.hpp"
#include "Constants.hpp"

class Player {
public:
    Player(float radius);
    void setPosition(float x, float y);
    void handleInput(bool spacePressed, bool moveLeft, bool moveRight, bool shiftPressed, float deltaTime);
    void update(float deltaTime, const sf::Vector2u& windowSize, const Platform& platform);
    void draw(sf::RenderWindow& window);
    
private:
    sf::CircleShape shape;
    sf::Texture texture;
    sf::Vector2f velocity{0, 0};
    bool canJump = false;
    float coyoteTime = 0.0f;

    void handleCollision(sf::Vector2f& newPos, const Platform& platform);
};

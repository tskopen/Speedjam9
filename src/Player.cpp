#include "Player.hpp"
#include "Platform.hpp"
#include "Constants.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace Constants;

Player::Player(float radius) : shape(radius) {
    sf::Texture slime;
    if (!slime.loadFromFile("textures/slimes.png", false, sf::IntRect({0, 0}, {256, 75})))
    {
        std::cout << "TEXTURE NOT RED" << std::endl;    
    }
    shape.setTexture(&slime); // texture is a sf::Texture
    shape.setTextureRect(sf::IntRect({0, 0}, {256, 75}));
    shape.setOrigin(sf::Vector2f{radius, radius});
}

void Player::setPosition(float x, float y) {
    shape.setPosition(sf::Vector2f{x, y});
}

void Player::handleInput(bool spacePressed, bool moveLeft, bool moveRight, bool shiftPressed, float deltaTime) {
    float targetSpeed = 0.0f;


    if (moveLeft != moveRight) {
        targetSpeed = moveLeft ? -MOVE_SPEED : MOVE_SPEED;
        //If shift is pressed then sprint.
        if (shiftPressed){
            {
                targetSpeed *= 2;
            }
        }
    }

    
    if (canJump) {
        velocity.x = targetSpeed;
    } else {
        velocity.x += (targetSpeed - velocity.x) * AIR_RESISTANCE;
    }

    if (canJump) {
        coyoteTime = COYOTE_TIME;
    } else {
        coyoteTime -= 1.0f/60.0f;
    }

    if (spacePressed && coyoteTime > 0) {
        velocity.y = JUMP_FORCE;
        canJump = false;
        coyoteTime = 0;
    }

}

void Player::update(float deltaTime, const sf::Vector2u& windowSize, const std::vector<Platform>& platforms) {
    velocity.y += GRAVITY * deltaTime;
    sf::Vector2f newPos = shape.getPosition() + velocity * deltaTime;
    for (const auto& platform : platforms) {
        handleCollision(newPos, platform);
    }
    float radius = shape.getRadius();
    newPos.x = std::clamp(newPos.x, radius, windowSize.x - radius);
    
    if (newPos.y > windowSize.y + radius * 2) {
        newPos = {windowSize.x/2.0f, windowSize.y/4.0f};
        velocity = {0, 0};
    }

    shape.setPosition(newPos);
}

void Player::handleCollision(sf::Vector2f& newPos, const Platform& platform) {
    sf::FloatRect platformBounds = platform.getBounds();
    const float radius = shape.getRadius();
    sf::Vector2f playerCenter = newPos;

    // SFML 3.0 Rect syntax
    float platformLeft = platformBounds.position.x;
    float platformRight = platformLeft + platformBounds.size.x;
    float platformTop = platformBounds.position.y;
    float platformBottom = platformTop + platformBounds.size.y;

    sf::Vector2f closestPoint(
        std::clamp(playerCenter.x, platformLeft, platformRight),
        std::clamp(playerCenter.y, platformTop, platformBottom)
    );

    sf::Vector2f collisionVec = closestPoint - playerCenter;
    float distanceSquared = collisionVec.x * collisionVec.x + collisionVec.y * collisionVec.y;
    float radiusSquared = radius * radius;

    if (distanceSquared > radiusSquared || distanceSquared < EPSILON) return;

    float actualDistance = std::sqrt(distanceSquared);
    sf::Vector2f normal = collisionVec / actualDistance;
    
    if (normal.y > 0.6f && velocity.y > 0) {
        newPos.y = platformTop - radius;
        velocity.y = 0;
        canJump = true;
    }
}

void Player::draw(sf::RenderWindow& window) {
    sf::Texture slime;
    //texture MUST be in the same function as window.draw, otherwise the texture lifespan expires and is not drawn. Issues are due to contrainerization... see docs
    if (!slime.loadFromFile("textures/slimes.png", false, sf::IntRect({0, 0}, {256, 75})))
    {
        std::cout << "TEXTURE NOT FOUND -Slimes" << std::endl;    
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        shape.setTextureRect(sf::IntRect({96, 25}, {32, 25}));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        shape.setTextureRect(sf::IntRect({256, 0}, {-32, 25}));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        shape.setTextureRect(sf::IntRect({96, 0}, {32, 25}));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        shape.setTextureRect(sf::IntRect({0, 25}, {32, 25}));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        shape.setTextureRect(sf::IntRect({64, 25}, {32, 25}));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
        shape.setFillColor(sf::Color::Red);
        shape.setTextureRect(sf::IntRect({96, 25}, {32, 25}));
    }
    else
    {
        shape.setFillColor(sf::Color(255, 255, 255));
        shape.setTexture(&slime); // texture is a sf::Texture
        shape.setTextureRect(sf::IntRect({0, 0}, {32, 25})); //Base texture
    }

    window.draw(shape);
}

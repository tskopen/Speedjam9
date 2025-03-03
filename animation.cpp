#include "animation.hpp"

JumpAnimation::JumpAnimation(sf::RenderWindow& window) 
    : m_window(window) {
    // Load texture
    if (!texture.loadFromFile("slimes.png")) {
        // Handle error
    }
    
    // Initialize sprite
    character.setTextureRect(sf::IntRect(96, 50, 32, 25));
}

void JumpAnimation::update() {
    // Handle animation logic
    if (clock.getElapsedTime().asSeconds() > 1.0f) {
        character.setTextureRect(sf::IntRect(32, 0, 32, 25));
        clock.restart();
    }

    // Handle input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        character.setTextureRect(sf::IntRect(96, 25, 32, 25));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        character.setTextureRect(sf::IntRect(256, 0, -32, 25));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        character.setTextureRect(sf::IntRect(96, 0, 32, 25));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        character.setTextureRect(sf::IntRect(0, 25, 32, 25));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        character.setTextureRect(sf::IntRect(64, 25, 32, 25));
    }
}

void JumpAnimation::draw() {
    window.draw(character);
}
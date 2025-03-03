#include "Game.hpp"
#include "Constants.hpp"

Game::Game() : 
    window(sf::VideoMode({800, 600}), "Platformer", sf::Style::Titlebar | sf::Style::Close),
    player(25),
    platform({400.0f, 30.0f}, {200.0f, 500.0f}) 
{
    player.setPosition(400.0f, 150.0f);
}

void Game::run() {
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        handleEvents();
        update(deltaTime);
        render();
    }
}

void Game::handleEvents() {
    while (auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>() ||
            (event->is<sf::Event::KeyPressed>() && 
             event->getIf<sf::Event::KeyPressed>()->scancode == sf::Keyboard::Scan::Escape)) {
            window.close();
        }
    }
}

void Game::update(float deltaTime) {
    bool spacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
    bool moveLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A);
    bool moveRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D);

    player.handleInput(spacePressed, moveLeft, moveRight);
    player.update(deltaTime, window.getSize(), platform);
}

void Game::render() {
    window.clear(sf::Color::Blue);
    platform.draw(window);
    player.draw(window);
    window.display();
}

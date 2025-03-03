#include "Game.hpp"
#include "Constants.hpp"

Game::Game() : 
    window(sf::VideoMode({1024, 1024}), "Platformer", sf::Style::Titlebar | sf::Style::Close),
    player(25)
    {
    player.setPosition(400.0f, 150.0f);
//Level layout
    platforms.emplace_back(sf::Vector2f(256.0f, 256.0f), sf::Vector2f(0.0f, 768.0f));
    platforms.emplace_back(sf::Vector2f(256.0f, 256.0f), sf::Vector2f(256.0f, 768.0f));
    platforms.emplace_back(sf::Vector2f(256.0f, 256.0f), sf::Vector2f(512.0f, 768.0f));


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
    bool shiftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::LShift);

    player.handleInput(spacePressed, moveLeft, moveRight, shiftPressed, deltaTime);
    for (const auto& platform : platforms) {
        player.update(deltaTime, window.getSize(), platform);
    }
    }

void Game::render() {
    window.clear(sf::Color::Blue);
    for (auto& platform : platforms) {
        platform.draw(window);
    };
    player.draw(window);
    window.display();
}

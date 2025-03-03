#include "Game.hpp"
#include "Constants.hpp"
#include <iostream>
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
    //Background
    sf::Texture tiles;
    sf::RectangleShape rectangle({1024.f, 1024.f});
    if (!tiles.loadFromFile("background.png", false, sf::IntRect({0, 0}, {765, 668})))
    {
        std::cout << "TEXTURE NOT FOUND -Background" << std::endl;    
    }
    rectangle.setTexture(&tiles); // texture is a sf::Texture
    rectangle.setTextureRect(sf::IntRect({0, 0}, {765, 668}));
    rectangle.setFillColor(sf::Color(141, 155, 184));

//End background


    window.draw(rectangle);
    for (auto& platform : platforms) {
        platform.draw(window);
    };
    player.draw(window);
    window.display();
}

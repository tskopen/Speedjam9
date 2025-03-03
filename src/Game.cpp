#include "Game.hpp"
#include "Constants.hpp"
#include <iostream>
Game::Game() : 
    window(sf::VideoMode({960, 960}), "Platformer", sf::Style::Titlebar | sf::Style::Close),
    player(25)
    {
    player.setPosition(192.0f, 800.0f);

//Level layout move blocks in 72 chunkcs
platforms.emplace_back(sf::Vector2f(288.0f, 96.0f), sf::Vector2f(0.0f, 864.0f));
platforms.emplace_back(sf::Vector2f(288.0f, 96.0f), sf::Vector2f(288.0f, 864.0f));

    


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
    sf::Texture background;
    sf::RectangleShape rectangle({960.f, 960.f});
    background.setRepeated(true);

    //texture MUST be in the same function as window.draw, otherwise the texture lifespan expires and is not drawn. Issues are due to contrainerization... see docs
    if (!background.loadFromFile("background.png", false))
    {
        std::cout << "TEXTURE NOT FOUND -background" << std::endl;    
    }
    rectangle.setTextureRect({{0, 0}, {960, 960}});
    rectangle.setTexture(&background); // texture is a sf::Texture
    window.draw(rectangle);

//End background


    window.draw(rectangle);
    for (auto& platform : platforms) {
        platform.draw(window);
    };
    player.draw(window);
    window.display();
}

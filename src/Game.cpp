#include "Game.hpp"
#include "Constants.hpp"
#include "Score.hpp"
#include <sstream>
#include <string>

#include <iostream>
Game::Game() : 
    window(sf::VideoMode({960, 960}), "Platformer", sf::Style::Titlebar | sf::Style::Close),
    player(25)
    {
    player.setPosition(192.0f, 800.0f);
    level();
}
void Game::level(){
    //Level layout move blocks in 72 chunks
    platforms.emplace_back(sf::Vector2f(288.0f, 96.0f), sf::Vector2f(0.0f, 864.0f), PlatformType::Standard);
    platforms.emplace_back(sf::Vector2f(96.0f, 24.0f), sf::Vector2f(72.0f, 792.0f), PlatformType::Standard);
    platforms.emplace_back(sf::Vector2f(288.0f, 96.0f), sf::Vector2f(72.0f, 576.0f), PlatformType::Standard);

    platforms.emplace_back(sf::Vector2f(288.0f, 96.0f), sf::Vector2f(288.0f, 864.0f), PlatformType::Slippery);
    platforms.emplace_back(sf::Vector2f(96.0f, 24.0f), sf::Vector2f(360.0f, 792.0f), PlatformType::Bouncy);
    platforms.emplace_back(sf::Vector2f(96.0f, 24.0f), sf::Vector2f(216.0f, 720.0f), PlatformType::Bouncy);
    platforms.emplace_back(sf::Vector2f(96.0f, 24.0f), sf::Vector2f(360.0f, 576.0f), PlatformType::Bouncy);
    platforms.emplace_back(sf::Vector2f(96.0f, 24.0f), sf::Vector2f(504.0f, 720.0f), PlatformType::Bouncy);


}

void Game::run() {
    while (window.isOpen()) {
        float deltaTime = deltaClock.restart().asSeconds();
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
    player.update(deltaTime, window.getSize(), platforms);
}
void Game::render() {
    //Background
    sf::Texture background;
    sf::RectangleShape rectangle({960.f, 960.f});
    background.setRepeated(true);

    //texture MUST be in the same function as window.draw, otherwise the texture lifespan expires and is not drawn. Issues are due to contrainerization... see docs
    if (!background.loadFromFile("textures/background.png", false))
    {
        std::cout << "TEXTURE NOT FOUND -background" << std::endl;    
    }
    rectangle.setTextureRect({{0, 0}, {960, 960}});
    rectangle.setTexture(&background); // texture is a sf::Texture

//End background
    //font
    if (!arcadeFont.openFromFile("textures/arcadeFont.ttf")) {
        std::cerr << "Failed to load arcadeFont.ttf!" << std::endl;
    }
//timer
    int elapsedTime = clock.getElapsedTime().asSeconds();

// Convert elapsedTime to a string
    std::ostringstream timeStream;
    timeStream << elapsedTime;
    std::string elapsedTimeStr = timeStream.str();  // Convert float to string
//timer end

    window.draw(rectangle);
    for (auto& platform : platforms) {
        platform.draw(window);
    };
    
    player.draw(window);
    score.draw(window, arcadeFont, elapsedTimeStr, 48, sf::Color::White, sf::Text::Bold, {0.f, 0.f});

    window.display();
    
}

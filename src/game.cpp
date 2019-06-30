#include <iostream>
#include "game.hpp"
#include "world.hpp"

const unsigned Game::s_windowWidth = sf::VideoMode::getDesktopMode().width * 2 / 3;
const unsigned Game::s_windowHeight = sf::VideoMode::getDesktopMode().height * 2 / 3;

sf::Time Game::s_tick = sf::seconds(1.0f);// / 60.0f);

Game::Game()
    : m_window(sf::VideoMode(s_windowWidth, s_windowHeight), "Game of Life")
{
    m_world = World::getInstance(s_windowWidth, s_windowHeight);
    m_world->initGrid(20, 10);
}


void Game::Run()
{
    sf::Clock clock;
    sf::Time lastUpdate = sf::Time::Zero;
    while (m_window.isOpen())
    {
        ProcessEvents();
        lastUpdate += clock.restart();

        if (lastUpdate > s_tick) {
            std::cout << "One second has passed" << std::endl;
            std::cout << lastUpdate.asMilliseconds() << std::endl;
            Update(s_tick.asSeconds());

            lastUpdate = sf::Time::Zero;
        }
        Render();
    }
}

void Game::Update(float dt)
{
}

void Game::Render()
{
    m_window.clear();
    m_world->drawGrid(m_window);
    m_window.display();
}


void Game::ProcessEvents()
{
    sf::Event event;

    while (m_window.pollEvent(event))
    {
        if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                || (event.type == sf::Event::Closed))
        {
            m_window.close();
        }

        if (event.type == sf::Event::MouseMoved)
            m_world->handleHover(event);

        if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
        {
            m_world->setIsMouseDown(true);
            m_world->handleClick(event);
        }

        if (event.type == sf::Event::MouseButtonReleased &&
                event.mouseButton.button == sf::Mouse::Left)
        {
            m_world->setIsMouseDown(false);
        }
    }
}


#include <iostream>
#include "game.hpp"
#include "world.hpp"

const unsigned Game::s_windowWidth = sf::VideoMode::getDesktopMode().width * 2 / 3;
const unsigned Game::s_windowHeight = sf::VideoMode::getDesktopMode().height * 2 / 3;

sf::Time Game::s_tick = sf::seconds(1.0f); // / 60.0f);

Game::Game()
    : m_window(sf::VideoMode(s_windowWidth, s_windowHeight), "Game of Life")
{
    m_world = World::getInstance(s_windowWidth, s_windowHeight);
    m_world->initGrid(20, 10);
}

Game::~Game()
{
    delete m_world;
}

void Game::Run()
{
    sf::Clock clock;
    sf::Time lastUpdate = sf::Time::Zero;
    while (m_window.isOpen())
    {
        ProcessEvents();
        lastUpdate += clock.restart();

        if (lastUpdate > s_tick)
        {
            Update(s_tick.asMilliseconds());
            lastUpdate = sf::Time::Zero;
        }
        Render();
    }
}

void Game::Update(float dt)
{
    std::cout << "One second has passed" << std::endl;
    std::cout << dt << std::endl;

    if (m_animate)
        m_world->updateGrid();
}

void Game::Render()
{
    m_window.clear();
    m_world->drawGrid(m_window);

    // sf::RectangleShape element;
    // element.setFillColor(sf::Color(0x00, 0x33, 0x66));
    // element.setSize(sf::Vector2f(300, 300));
    // element.setPosition(0,0);
    // m_window.draw(element);

    // std::cout << "Crtam " << i << "," << j << " isOn: " << element.isOn() << std::endl;

    m_window.display();
}

void Game::ProcessEvents()
{
    sf::Event event;

    while (m_window.pollEvent(event))
    {
        if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || (event.type == sf::Event::Closed))
        {
            m_window.close();
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G)
        {
            m_animate = !m_animate;
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
        {
            m_world->clearGrid();
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

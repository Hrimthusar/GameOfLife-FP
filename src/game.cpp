#include <iostream>
#include "game.hpp"
#include "world.hpp"

const unsigned Game::s_windowWidth = sf::VideoMode::getDesktopMode().width * 2 / 3;
const unsigned Game::s_windowHeight = sf::VideoMode::getDesktopMode().height * 2 / 3;

sf::Time Game::s_tick = sf::seconds(1.0f);
sf::Time Game::s_fastestTick = sf::seconds(0.1f);
sf::Time Game::s_slowestTick = sf::seconds(2.0f);
sf::Time Game::s_tickChange = sf::seconds(0.1f);
int Game::s_xGridSize = 10;
int Game::s_yGridSize = 20;
int Game::s_xGridChange = 5;
int Game::s_yGridChange = 10;

Game::Game()
    : m_window(sf::VideoMode(s_windowWidth, s_windowHeight), "Game of Life")
{
    m_world = World::getInstance(s_windowWidth, s_windowHeight);
    m_world->initGrid(s_xGridSize, s_yGridSize);
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
    (void)dt;

    if (m_animate)
        m_world->updateGrid();
}

void Game::Render()
{
    m_window.clear();
    m_world->drawGrid(m_window);
    m_world->drawInfo(m_window, s_tick, m_animate, s_xGridSize, s_yGridSize);
    m_window.display();
}

void Game::processKeyboardEvents(sf::Event &event)
{
    switch (event.key.code)
    {
    case sf::Keyboard::Escape:
    case sf::Keyboard::X:
        // close the application
        m_window.close();
        break;
    case sf::Keyboard::G:
        // start/stop the animation
        m_animate = !m_animate;
        break;

    case sf::Keyboard::R:
        // clear the grid
        m_world->clearGrid();
        break;

    case sf::Keyboard::H:
        // higher speed
        if (s_tick > s_fastestTick)
            s_tick -= s_tickChange;
        break;

    case sf::Keyboard::L:
        // lower speed
        if (s_tick < s_slowestTick)
            s_tick += s_tickChange;
        break;

    case sf::Keyboard::B:
        // bigger grid
        s_xGridSize += s_xGridChange;
        s_yGridSize += s_yGridChange;

        m_world->initGrid(s_xGridSize, s_yGridSize);
        break;

    case sf::Keyboard::S:
        // smaller grid
        if (s_xGridSize > s_xGridChange)
            s_xGridSize -= s_xGridChange;
        if (s_yGridSize > s_yGridChange)
            s_yGridSize -= s_yGridChange;

        m_world->initGrid(s_xGridSize, s_yGridSize);
        break;
    default:
        break;
    }
}

void Game::ProcessEvents()
{
    sf::Event event;

    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window.close();
        }

        if (event.type == sf::Event::KeyPressed)
            processKeyboardEvents(event);

        if (event.type == sf::Event::MouseMoved)
            m_world->handleHover(event);

        if (event.type == sf::Event::MouseButtonPressed
            // && event.mouseButton.button == sf::Mouse::Left
            )
        {
            m_world->setIsMouseDown(true);
            m_world->handleClick(event);
        }

        if (event.type == sf::Event::MouseButtonReleased
            // && event.mouseButton.button == sf::Mouse::Left
            )
        {
            m_world->setIsMouseDown(false);
        }
    }
}

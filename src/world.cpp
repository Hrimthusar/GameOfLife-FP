#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "world.hpp"
#include "cell.hpp"

/* Null, because instance will be initialized on demand. */
World *World::instance = NULL;

/* Initializing cell colors */
const sf::Color World::clrClickedCell  = sf::Color(0x00, 0x33, 0x66);
const sf::Color World::clrHoveredCell  = sf::Color(0x00, 0xFF, 0xFF);
const sf::Color World::clrBlankCell    = sf::Color(0xCC, 0xFF, 0xFF);

World *World::getInstance(unsigned w, unsigned h)
{
    if (instance == NULL)
    {
        instance = new World(w, h);
    }

    return instance;
}

World::World(unsigned w, unsigned h)
    // : screenWidth(w), screenHeight(h)
{
    std::cout << w << " " << h << std::endl;
    screenWidth = w;
    screenHeight = h;
}

void World::initGrid(unsigned m, unsigned n)
{
    xCount = m;
    yCount = n;

    unsigned cellSizeX = (screenWidth - cellMargin) / xCount;
    unsigned cellSizeY = (screenHeight - cellMargin) / yCount;

    cellSize = std::min(cellSizeX, cellSizeY) - cellMargin;

    innerWidth = ((cellSize + cellMargin) * xCount) - cellMargin;
    innerHeight = ((cellSize + cellMargin) * yCount) - cellMargin;

    unsigned topPadding = (screenHeight % innerHeight) / 2;
    unsigned leftPadding = (screenWidth % innerWidth) / 2;

    grid.resize(xCount);
    for (unsigned i = 0; i < xCount; ++i)
        grid[i].resize(yCount);

    std::cout << "Mate" << grid[0][0].is_hovered() << std::endl;

    for (unsigned i = 0; i < xCount; ++i)
    {
        for (unsigned j = 0; j < yCount; ++j)
        {
            grid[i][j].body().setSize(sf::Vector2f(cellSize, cellSize));
            grid[i][j].body().setPosition(leftPadding + i * (cellMargin + cellSize),
                    topPadding + j * (cellMargin + cellSize));

            if (grid[i][j].is_on() == 0)
                grid[i][j].body().setFillColor(sf::Color::Blue);
            else
                grid[i][j].body().setFillColor(sf::Color::Cyan);
        }
    }
};

void World::handleHover(sf::Event &event)
{
    // TODO create a coordinateToCellIndex function
    auto &mouseX = event.mouseMove.x;
    auto &mouseY = event.mouseMove.y;

    //                  TODO: Left padding
    auto x = (mouseX - (screenWidth % innerWidth) / 2) / (cellSize + cellMargin);
    //                  TODO: Top padding
    auto y = (mouseY - (screenHeight % innerHeight) / 2) / (cellSize + cellMargin);

    std::cout << x << "," << y << std::endl;

    for (unsigned i = 0; i < xCount; ++i)
    {
        for (unsigned j = 0; j < yCount; ++j)
        {
            grid[i][j].set_is_hovered(false);
        }
    }

    if (x >= 0 && x < xCount && y >= 0 && y < yCount)
        grid[x][y].set_is_hovered(true);
}

void World::handleClick(sf::Event &event)
{
    auto &mouseX = event.mouseButton.x;
    auto &mouseY = event.mouseButton.y;

    //                  TODO: Left padding
    auto x = (mouseX - (screenWidth % innerWidth) / 2) / (cellSize + cellMargin);
    //                  TODO: Top padding
    auto y = (mouseY - (screenHeight % innerHeight) / 2) / (cellSize + cellMargin);

    //std::cout << x << "," << y << std::endl;
    if (x >= 0 && x < xCount && y >= 0 && y < yCount)
        grid[x][y].set_is_on(!grid[x][y].is_on());
}

// if (event.type == sf::Event::MouseMoved)
// {
//     std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
//     std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
// }

void World::drawGrid(sf::RenderWindow &window)
{
    for (unsigned i = 0; i < xCount; ++i)
    {
        for (unsigned j = 0; j < yCount; ++j)
        {
            if (grid[i][j].is_on())
                grid[i][j].body().setFillColor(clrClickedCell);
            else if (grid[i][j].is_hovered())
                grid[i][j].body().setFillColor(clrHoveredCell);
            else
                grid[i][j].body().setFillColor(clrBlankCell);
            window.draw(grid[i][j].body());
        }
    }
}

#include <SFML/Graphics.hpp>
#include <iostream>

#include "misc.hpp"

class World
{
private:
    /* Here will be the instance stored. */
    static World *instance;

    /* Private constructor to prevent instancing. */
    World(unsigned w, unsigned h);

    unsigned screenWidth;
    unsigned screenHeight;

    unsigned innerWidth;
    unsigned innerHeight;

    unsigned xCount;
    unsigned yCount;

    unsigned cellSize;

    unsigned cellMargin = 5;

    std::vector<std::vector<sf::RectangleShape>> grid;

public:
    /* Static access method. */
    static World *getInstance(unsigned w, unsigned h);

    void initGrid(unsigned m, unsigned n);
    void drawGrid(sf::RenderWindow &window);
};

/* Null, because instance will be initialized on demand. */
World *World::instance = NULL;

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

    for (unsigned i = 0; i < xCount; ++i)
    {
        for (unsigned j = 0; j < yCount; ++j)
        {
            grid[i][j] = sf::RectangleShape(sf::Vector2f(cellSize, cellSize));
            grid[i][j].setPosition(leftPadding + i * (cellMargin + cellSize),
                                   topPadding + j * (cellMargin + cellSize));
            grid[i][j].setFillColor(sf::Color::Blue);
        }
    }
};

void World::drawGrid(sf::RenderWindow &window)
{
    for (unsigned i = 0; i < xCount; ++i)
    {
        for (unsigned j = 0; j < yCount; ++j)
        {
            window.draw(grid[i][j]);
        }
    }
}

int main()
{
    const unsigned w = 800;
    const unsigned h = 600;
    sf::RenderWindow window(sf::VideoMode(w, h), "SFML works!");

    World *world = World::getInstance(w, h);
    world->initGrid(20, 10);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        world->drawGrid(window);

        window.display();
    }

    std::cout << misc::meaning_of_life() << std::endl;
    misc::test_range();

    return 0;
}

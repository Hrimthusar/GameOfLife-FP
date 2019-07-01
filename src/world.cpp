#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "world.hpp"
#include "cell.hpp"

/* Null, because instance will be initialized on demand. */
World *World::s_instance = NULL;

/* Initializing cell colors */
const sf::Color World::clrClickedCell = sf::Color(0x00, 0x33, 0x66);
const sf::Color World::clrClickedHoveredCell = sf::Color(0x00, 0x99, 0xFF);
const sf::Color World::clrHoveredCell = sf::Color(0x00, 0xFF, 0xFF);
const sf::Color World::clrBlankCell = sf::Color(0xCC, 0xFF, 0xFF);

World *World::getInstance(unsigned w, unsigned h)
{
    if (s_instance == NULL)
    {
        s_instance = new World(w, h);
    }

    return s_instance;
}

World::World(unsigned w, unsigned h)
    : screenWidth(w), screenHeight(h)
// , grid()
{
}

bool World::isMouseDown() const
{
    return m_isMouseDown;
}

std::pair<unsigned, unsigned> World::getCellFromMouse(int mouseX, int mouseY)
{
    auto x = (mouseX - leftPadding()) / (cellSize + cellMargin);
    auto y = (mouseY - topPadding()) / (cellSize + cellMargin);

    return std::make_pair(x, y);
}

unsigned World::leftPadding()
{
    return (screenWidth - innerWidth) / 2;
}
unsigned World::topPadding()
{
    return (screenHeight - innerHeight) / 2;
}

void World::setIsMouseDown(bool isMouseDown)
{
    m_isMouseDown = isMouseDown;
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

    grid.resizeMatrix(xCount, yCount);

    for (unsigned i = 0; i < xCount; ++i)
    {
        for (unsigned j = 0; j < yCount; ++j)
        {

            auto &element = grid[std::make_pair(i, j)];

            element.body().setSize(sf::Vector2f(cellSize, cellSize));
            std::cout << i << ", " << j << std::endl;

            element.body().setPosition(leftPadding() + i * (cellMargin + cellSize),
                                       topPadding() + j * (cellMargin + cellSize));

            std::cout << element.body().getPosition().x
                      << "," << element.body().getPosition().y << std::endl;

            std::cout
                << "^^^^^^^ " << std::endl;

            if (element.isOn() == 0)
                element.body().setFillColor(clrBlankCell);
            else
                element.body().setFillColor(clrClickedCell);
        }
    }
};

void World::handleHover(sf::Event &event)
{
    auto cellCoords = getCellFromMouse(event.mouseMove.x, event.mouseMove.y);
    auto x = cellCoords.first;
    auto y = cellCoords.second;

    bool wasHovered;
    if (x < xCount && y < yCount)
        wasHovered = grid[std::make_pair(x, y)].isHovered();

    for (unsigned i = 0; i < xCount; ++i)
    {
        for (unsigned j = 0; j < yCount; ++j)
        {
            grid[std::make_pair(i, j)].set_isHovered(false);
        }
    }

    if (x < xCount && y < yCount)
    {
        // std::cout << "Hoverovan :" << x << "," << y << std::endl;
        if (isMouseDown() && !wasHovered)
            grid[std::make_pair(x, y)].set_isOn(!grid[std::make_pair(x, y)].isOn());

        grid[std::make_pair(x, y)].set_isHovered(true);
    }
}

void World::handleClick(sf::Event &event)
{
    auto cellCoords = getCellFromMouse(event.mouseButton.x, event.mouseButton.y);
    auto x = cellCoords.first;
    auto y = cellCoords.second;

    if (x >= 0 && x < xCount && y >= 0 && y < yCount)
        grid[std::make_pair(x, y)].set_isOn(!grid[std::make_pair(x, y)].isOn());
}

void World::drawGrid(sf::RenderWindow &window)
{
    // for (unsigned i = 0; i < xCount; ++i)
    // {
    //     for (unsigned j = 0; j < yCount; ++j)
    //     {
    //         auto &element = grid[std::make_pair(i, j)];

    //         std::cout << "Crtam " << i << "," << j <<
    //         " pos: " << element.body().getPosition().x << ","
    //         << element.body().getPosition().x << std::endl;

    //         if (element.isOn() && element.isHovered())
    //             element.body().setFillColor(clrClickedHoveredCell);
    //         else if (element.isOn())
    //             element.body().setFillColor(clrClickedCell);
    //         else if (element.isHovered())
    //             element.body().setFillColor(clrHoveredCell);
    //         else
    //             element.body().setFillColor(clrBlankCell);
    //         window.draw(element.body());
    //     }
    // }

    int i = 0;
    for (auto it = grid.begin(); it != grid.end(); ++it)
    {
        std::cout << "ITERATOR " << i++ << std::endl;
        auto element = *it;
        if (element.isOn() && element.isHovered())
            element.body().setFillColor(clrClickedHoveredCell);
        else if (element.isOn())
            element.body().setFillColor(clrClickedCell);
        else if (element.isHovered())
            element.body().setFillColor(clrHoveredCell);
        else
            element.body().setFillColor(clrBlankCell);
        window.draw(element.body());
    }
}

void World::updateGrid()
{
    static std::vector<std::vector<int>> count_cell(xCount, std::vector<int>(yCount, 0));

    for (unsigned i = 0; i < xCount; ++i)
    {
        for (unsigned j = 0; j < yCount; ++j)
        {
            count_cell[i][j] = 0;
            std::vector<int> move{-1, 0, 1};
            for (int i_move : move)
            {
                for (int j_move : move)
                {
                    int x_new = i + i_move;
                    int y_new = j + j_move;
                    if (x_new >= 0 && x_new < static_cast<int>(xCount) && y_new >= 0 && y_new < static_cast<int>(yCount) && (i_move != 0 || j_move != 0))
                    {
                        count_cell[i][j] += grid[std::make_pair(x_new, y_new)].isOn();
                    }
                }
            }
        }
    }

    for (unsigned i = 0; i < xCount; ++i)
    {
        for (unsigned j = 0; j < yCount; ++j)
        {
            auto &element = grid[(std::make_pair(i, j))];
            if (element.isOn() && (count_cell[i][j] < 2 || count_cell[i][j] > 3))
            {
                element.set_isOn(false);
            }
            if (!element.isOn() && count_cell[i][j] == 3)
            {
                element.set_isOn(true);
            }
        }
    }
}

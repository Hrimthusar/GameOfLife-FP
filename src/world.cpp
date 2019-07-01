#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "world.hpp"
#include "cell.hpp"
#include <algorithm>
#include <range/v3/view/cartesian_product.hpp>

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

    for (auto it = grid.begin(); it != grid.end(); ++it)
    {
        Cell& element = *it;
        auto indices = it.getIndices();

        element.body().setSize(sf::Vector2f(cellSize, cellSize));
        element.body().setPosition(leftPadding() + indices.first * (cellMargin + cellSize),
                                   topPadding() + indices.second * (cellMargin + cellSize));
    }
};

void World::clearGrid()
{
    for (auto& element : grid)
        element.setIsOn(false);
}

void World::handleHover(sf::Event &event)
{
    auto cellCoords = getCellFromMouse(event.mouseMove.x, event.mouseMove.y);
    auto x = cellCoords.first;
    auto y = cellCoords.second;

    bool wasHovered;
    if (grid.indicesInBounds(x, y))
        wasHovered = grid[std::make_pair(x, y)].isHovered();

    for (auto& element : grid)
        element.setIsHovered(false);

    if (grid.indicesInBounds(x, y))
    {
        if (isMouseDown() && !wasHovered)
            grid[std::make_pair(x, y)].setIsOn(!grid[std::make_pair(x, y)].isOn());

        grid[std::make_pair(x, y)].setIsHovered(true);
    }
}

void World::handleClick(sf::Event &event)
{
    auto cellCoords = getCellFromMouse(event.mouseButton.x, event.mouseButton.y);
    auto x = cellCoords.first;
    auto y = cellCoords.second;

    if (grid.indicesInBounds(x, y))
        grid[std::make_pair(x, y)].setIsOn(!grid[std::make_pair(x, y)].isOn());
}

void World::drawGrid(sf::RenderWindow &window)
{
    for (auto& el : grid)
    {
        el.setCellColor();
        window.draw(el.body());
    }
}

void World::updateNeighbourCount(std::pair<int, int> indices,
                                    std::vector<std::vector<int>>& count_cell)
{
    int i = indices.first;
    int j = indices.second;

    static std::vector<int> step{-1, 0, 1};
    static auto steps = ranges::v3::view::cartesian_product(step, step);

    for (std::tuple<int, int> &&el : steps)
    {
        int i_step = std::get<0>(el);
        int j_step = std::get<1>(el);
        int x_new = i + i_step;
        int y_new = j + j_step;

        if (grid.indicesInBounds(x_new, y_new) && (i_step != 0 || j_step != 0))
            count_cell[x_new][y_new] += 1;
    }
}

void World::updateGrid()
{
    std::vector<std::vector<int>> count_cell(xCount, std::vector<int>(yCount, 0));

    for (auto it = grid.begin(); it != grid.end(); ++it)
    {
        Cell& element = *it;
        auto indices = it.getIndices();

        if (element.isOn())
            updateNeighbourCount(indices, count_cell);
    }

    for (auto it = grid.begin(); it != grid.end(); ++it)
    {
        Cell& element = *it;
        auto indices = it.getIndices();
        int x = indices.first;
        int y = indices.second;

        if (element.isOn() && (count_cell[x][y] < 2 || count_cell[x][y] > 3))
            element.setIsOn(false);
        else if (!element.isOn() && count_cell[x][y] == 3)
            element.setIsOn(true);
    }
}

// void World::updateGridOld()
// {
//     static std::vector<std::vector<int>> count_cell(xCount, std::vector<int>(yCount, 0));
//
//     for (unsigned i = 0; i < xCount; ++i)
//     {
//         for (unsigned j = 0; j < yCount; ++j)
//         {
//             count_cell[i][j] = 0;
//             std::vector<int> move{-1, 0, 1};
//             for (int i_move : move)
//             {
//                 for (int j_move : move)
//                 {
//                     int x_new = i + i_move;
//                     int y_new = j + j_move;
//                     if (x_new >= 0 && x_new < static_cast<int>(xCount) && y_new >= 0 && y_new < static_cast<int>(yCount) && (i_move != 0 || j_move != 0))
//                     {
//                         count_cell[i][j] += grid[std::make_pair(x_new, y_new)].isOn();
//                     }
//                 }
//             }
//         }
//     }
//
//     for (unsigned i = 0; i < xCount; ++i)
//     {
//         for (unsigned j = 0; j < yCount; ++j)
//         {
//             auto &element = grid[(std::make_pair(i, j))];
//             if (element.isOn() && (count_cell[i][j] < 2 || count_cell[i][j] > 3))
//             {
//                 element.setIsOn(false);
//             }
//             if (!element.isOn() && count_cell[i][j] == 3)
//             {
//                 element.setIsOn(true);
//             }
//         }
//     }
// }

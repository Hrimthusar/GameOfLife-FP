#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <tuple>
#include <range/v3/view.hpp>
#include <range/v3/algorithm/count_if.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include "world.hpp"
#include "cell.hpp"

using namespace ranges::v3;


/* Null, because instance will be initialized on demand. */
World *World::s_instance = NULL;

/* Initializing cell colors */
const sf::Color World::clrClickedCell = sf::Color(0x00, 0x33, 0x66);
const sf::Color World::clrClickedHoveredCell = sf::Color(0x00, 0x99, 0xFF);
const sf::Color World::clrHoveredCell = sf::Color(0x00, 0xFF, 0xFF);
const sf::Color World::clrBlankCell = sf::Color(0xCC, 0xFF, 0xFF);

sf::Font World::font;

World *World::getInstance(unsigned w, unsigned h)
{
    if (s_instance == NULL)
    {
        s_instance = new World(w, h);
    }

    return s_instance;
}

World::World(unsigned w, unsigned h)
    : m_screenWidth(w), m_screenHeight(h)
{
    if (!font.loadFromFile("resources/fonts/arcadeclassic.ttf"))
    {
        throw std::runtime_error("Could not open file");
    }
}

bool World::isMouseDown() const
{
    return m_isMouseDown;
}

std::pair<unsigned, unsigned> World::getCellFromMouse(int mouseX, int mouseY)
{
    auto i = (mouseY - topPadding()) / (m_cellSize + m_cellMargin);
    auto j = (mouseX - leftPadding()) / (m_cellSize + m_cellMargin);

    return std::make_pair(i, j);
}

unsigned World::leftPadding()
{
    return (m_screenWidth - m_innerWidth) / 2;
}
unsigned World::topPadding()
{
    return (m_screenHeight - m_innerHeight) / 2;
}

void World::setIsMouseDown(bool isMouseDown)
{
    m_isMouseDown = isMouseDown;
}

void World::initGrid(unsigned xNum, unsigned yNum)
{
    m_xCount = xNum;
    m_yCount = yNum;

    unsigned cellSizeX = (m_screenHeight - m_cellMargin - m_statusHeight*2) / m_xCount;
    unsigned cellSizeY = (m_screenWidth - m_cellMargin) / m_yCount;

    m_cellSize = std::min(cellSizeX, cellSizeY) - m_cellMargin;

    m_innerWidth = ((m_cellSize + m_cellMargin) * m_yCount) - m_cellMargin;
    m_innerHeight = ((m_cellSize + m_cellMargin) * m_xCount) - m_cellMargin;

    m_grid.resizeMatrix(m_xCount, m_yCount);

    for (auto it = m_grid.begin(); it != m_grid.end(); ++it)
    {
        Cell &element = *it;
        auto indices = it.getIndices();

        element.body().setSize(sf::Vector2f(m_cellSize, m_cellSize));
        element.body().setPosition(leftPadding() + indices.second * (m_cellMargin + m_cellSize),
                                   topPadding() + indices.first * (m_cellMargin + m_cellSize));
    }
};

void World::clearGrid()
{
    for (auto &element : m_grid)
        element.setIsOn(false);
}

void World::handleHover(sf::Event &event)
{
    auto cellCoords = getCellFromMouse(event.mouseMove.x, event.mouseMove.y);
    auto x = cellCoords.first;
    auto y = cellCoords.second;

    bool wasHovered;
    if (m_grid.indicesInBounds(x, y))
        wasHovered = m_grid[cellCoords].isHovered();

    for (auto &element : m_grid)
        element.setIsHovered(false);

    if (m_grid.indicesInBounds(x, y))
    {
        if (isMouseDown() && !wasHovered) {
            if(m_grid[cellCoords].isOn()){
                --m_cellCount;
                m_grid[cellCoords].setIsOn(false);
            } else {
                ++m_cellCount;
                m_grid[cellCoords].setIsOn(true);
            }
        }

        m_grid[cellCoords].setIsHovered(true);
    }
}

void World::handleClick(sf::Event &event)
{
    auto cellCoords = getCellFromMouse(event.mouseButton.x, event.mouseButton.y);
    auto x = cellCoords.first;
    auto y = cellCoords.second;

    if (m_grid.indicesInBounds(x, y)) {
        if(m_grid[cellCoords].isOn()){
            --m_cellCount;
            m_grid[cellCoords].setIsOn(false);
        } else {
            ++m_cellCount;
            m_grid[cellCoords].setIsOn(true);
        }
    }
}

void World::drawGrid(sf::RenderWindow &window)
{
    for (auto &el : m_grid)
    {
        el.setCellColor();
        window.draw(el.body());
    }
}

void World::drawInfo(sf::RenderWindow &window, sf::Time tick,
                     bool animate, int xSize, int ySize)
{
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(m_statusHeight - 20);
    text.setFillColor(sf::Color::White);
    text.setPosition(20, 10);

    const auto separator = "   |   ";

    std::ostringstream oss;
    oss << "population   " << m_cellCount << separator
        << "tick " << tick.asMilliseconds() << separator
        << "size " << xSize << " x " << ySize << separator
        << "play " << animate;

    text.setString(oss.str());
    window.draw(text);
}

std::vector<bool> World::calculateNewCellsStatus() const
{
    auto niz = m_grid.asRange();

    auto countedNeighbours =
            view::cartesian_product(view::ints(0, (int)m_xCount), view::ints(0, (int)m_yCount))
            | view::transform([&](auto indexedCell)
                        {return this->m_grid.countNeighbours(indexedCell);});

    auto cellsStatus =
        niz | view::transform([](auto indexedCell){return indexedCell.isOn();});

    return view::zip(countedNeighbours, cellsStatus)
            | view::transform(Cell::applyRules);
}


void World::updateGrid()
{
    std::vector<bool> newCellsStatus = calculateNewCellsStatus();

    int i=0;
    m_cellCount = 0;
    for (auto &element : m_grid){
        element.setIsOn(newCellsStatus[i]);
        m_cellCount += newCellsStatus[i];
        i++;
    }
}

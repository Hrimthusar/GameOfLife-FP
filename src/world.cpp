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
    : screenWidth(w), screenHeight(h)
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
    auto i = (mouseY - topPadding()) / (cellSize + cellMargin);
    auto j = (mouseX - leftPadding()) / (cellSize + cellMargin);

    return std::make_pair(i, j);
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

void World::initGrid(unsigned xNum, unsigned yNum)
{
    xCount = xNum;
    yCount = yNum;

    unsigned cellSizeX = (screenHeight - cellMargin - statusHeight*2) / xCount;
    unsigned cellSizeY = (screenWidth - cellMargin) / yCount;

    cellSize = std::min(cellSizeX, cellSizeY) - cellMargin;

    innerWidth = ((cellSize + cellMargin) * yCount) - cellMargin;
    innerHeight = ((cellSize + cellMargin) * xCount) - cellMargin;

    grid.resizeMatrix(xCount, yCount);

    for (auto it = grid.begin(); it != grid.end(); ++it)
    {
        Cell &element = *it;
        auto indices = it.getIndices();

        element.body().setSize(sf::Vector2f(cellSize, cellSize));
        element.body().setPosition(leftPadding() + indices.second * (cellMargin + cellSize),
                                   topPadding() + indices.first * (cellMargin + cellSize));
    }
};

void World::clearGrid()
{
    for (auto &element : grid)
        element.setIsOn(false);
}

void World::handleHover(sf::Event &event)
{
    auto cellCoords = getCellFromMouse(event.mouseMove.x, event.mouseMove.y);
    auto x = cellCoords.first;
    auto y = cellCoords.second;

    bool wasHovered;
    if (grid.indicesInBounds(x, y))
        wasHovered = grid[cellCoords].isHovered();

    for (auto &element : grid)
        element.setIsHovered(false);

    if (grid.indicesInBounds(x, y))
    {
        if (isMouseDown() && !wasHovered) {
            if(grid[cellCoords].isOn()){
                --cellCount;
                grid[cellCoords].setIsOn(false);
            } else {
                ++cellCount;
                grid[cellCoords].setIsOn(true);
            }
        }

        grid[cellCoords].setIsHovered(true);
    }
}

void World::handleClick(sf::Event &event)
{
    auto cellCoords = getCellFromMouse(event.mouseButton.x, event.mouseButton.y);
    auto x = cellCoords.first;
    auto y = cellCoords.second;

    if (grid.indicesInBounds(x, y)) {
        if(grid[cellCoords].isOn()){
            --cellCount;
            grid[cellCoords].setIsOn(false);
        } else {
            ++cellCount;
            grid[cellCoords].setIsOn(true);
        }
    }
}

void World::drawGrid(sf::RenderWindow &window)
{
    for (auto &el : grid)
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
    text.setCharacterSize(statusHeight - 20);
    text.setFillColor(sf::Color::White);
    text.setPosition(20, 10);

    const auto separator = "   |   ";

    std::ostringstream oss;
    oss << "population   " << cellCount << separator
        << "tick " << tick.asMilliseconds() << separator
        << "size " << xSize << " x " << ySize << separator
        << "play " << animate;

    text.setString(oss.str());
    window.draw(text);
}

int World::countNeighbours(std::pair<Cell, ranges::common_tuple<int, int>> indexedCell)
{
    int i = std::get<0>(indexedCell.second);
    int j = std::get<1>(indexedCell.second);

    static std::vector<int> step{-1, 0, 1};
    static auto steps = view::cartesian_product(step, step);

    return count_if(steps,
        [=](auto s){
            return this->grid.indicesInBounds(std::get<0>(s) + i, std::get<1>(s) + j)
            && (std::get<0>(s) != 0 || std::get<1>(s) != 0)
            && this->grid[std::make_pair(std::get<0>(s)+i,std::get<1>(s)+j)].isOn();
        });
}

static bool applyRules(std::pair<int, bool> element) {
    auto neighboursCount = element.first;
    auto alive = element.second;

    if (alive && (neighboursCount < 2 || neighboursCount > 3)) {
        return false;
    }
    else if (!alive && neighboursCount == 3)
    {
        return true;
    }
    return alive;
}

void World::updateGrid()
{
    auto niz = grid.asRange();

    std::vector<bool> result =
        view::zip(
            view::zip (
                niz,
                view::cartesian_product(view::ints(0, (int)xCount), view::ints(0, (int)yCount)) 
            )                
            | view::transform([=](auto indexedCell){return this->countNeighbours(indexedCell); }), // vraca vektor intova

            niz | view::transform([](auto indexedCell){return indexedCell.isOn(); }) // vraca 2d niz boolova
        )
        | view::transform(applyRules);

    int i=0;
    cellCount = 0;
    for (auto &element : grid){
        element.setIsOn(result[i]);
        cellCount += result[i];
        i++;
    }
}
#ifndef WORLD_H // include guard
#define WORLD_H

#include <SFML/Graphics.hpp>
#include "grid.hpp"
#include "cell.hpp"
#include <range/v3/view.hpp>


using namespace ranges::v3;


class World
{
private:
    /* Here will be the instance stored. */
    static World *s_instance;

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

    unsigned statusHeight = 50;

    unsigned cellCount = 0;

    bool m_isMouseDown = false;

    Grid grid;

public:
    /* Static access method. */
    static World *getInstance(unsigned w, unsigned h);

    std::pair<unsigned, unsigned> getCellFromMouse(int mouseX, int mouseY);

    unsigned leftPadding();
    unsigned topPadding();

    void initGrid(unsigned xNum, unsigned yNum);
    void clearGrid();
    void drawGrid(sf::RenderWindow &window);
    void drawInfo(sf::RenderWindow &window, sf::Time tick,
                  bool animate, int s_xGridSize, int s_yGridSize);
    // void updateGridOld();
    void updateGrid();
    int countNeighbours(std::pair<Cell, ranges::common_tuple<int, int>> indexedCell);

    void handleHover(sf::Event &event);
    void handleClick(sf::Event &event);

    bool isMouseDown() const;
    void setIsMouseDown(bool isMouseDown);

    /* Colors of cells */
    static const sf::Color clrClickedCell;
    static const sf::Color clrClickedHoveredCell;
    static const sf::Color clrHoveredCell;
    static const sf::Color clrBlankCell;

    static sf::Font font;
};

#endif /* WORLD_H */

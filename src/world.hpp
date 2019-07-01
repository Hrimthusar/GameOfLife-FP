#ifndef WORLD_H // include guard
#define WORLD_H

#include <SFML/Graphics.hpp>
#include "grid.hpp"
#include "cell.hpp"

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

    bool m_isMouseDown = false;

    Grid grid;

public:
    /* Static access method. */
    static World *getInstance(unsigned w, unsigned h);

    std::pair<unsigned, unsigned> getCellFromMouse(int mouseX, int mouseY);

    unsigned leftPadding();
    unsigned topPadding();

    void initGrid(unsigned m, unsigned n);
    void clearGrid();
    void drawGrid(sf::RenderWindow &window);
    void updateGridOld();
    void updateGrid();
    void updateNeighbourCount(std::pair<int, int> indices,
                                std::vector<std::vector<int>>& count_cell);

    void handleHover(sf::Event &event);
    void handleClick(sf::Event &event);

    bool isMouseDown() const;
    void setIsMouseDown(bool isMouseDown);

    /* Colors of cells */
    static const sf::Color clrClickedCell;
    static const sf::Color clrClickedHoveredCell;
    static const sf::Color clrHoveredCell;
    static const sf::Color clrBlankCell;
};

#endif /* WORLD_H */

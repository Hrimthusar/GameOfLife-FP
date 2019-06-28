#ifndef WORLD_H // include guard
#define WORLD_H

#include <SFML/Graphics.hpp>
#include "cell.hpp"

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

    std::vector<std::vector<Cell>> grid;

public:
    /* Static access method. */
    static World *getInstance(unsigned w, unsigned h);

    void initGrid(unsigned m, unsigned n);
    void drawGrid(sf::RenderWindow &window);
    void handleHover(sf::Event &event);
    void handleClick(sf::Event &event);

    /* Colors of cells */
    static const sf::Color clrClickedCell;
    static const sf::Color clrHoveredCell;
    static const sf::Color clrBlankCell;
};

#endif /* WORLD_H */

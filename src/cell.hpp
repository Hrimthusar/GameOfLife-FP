#ifndef CELL_H // include guard
#define CELL_H

#include <SFML/Graphics.hpp>

class Cell
{
public:
    Cell();
    Cell(sf::RectangleShape body);
    Cell(const Cell &other);
    Cell(Cell &&other);
    ~Cell();

    Cell& operator=(Cell other);

    friend void swap(Cell& first, Cell& second);

    sf::RectangleShape &body();
    const sf::RectangleShape &body() const;

    bool isOn() const;
    Cell withIsOn(bool isOn) &&;

    void updateCellColor(bool isHovered);

    static bool applyRules(const std::pair<int, bool> element);

    static const sf::Color s_clrClickedCell;
    static const sf::Color s_clrClickedHoveredCell;
    static const sf::Color s_clrHoveredCell;
    static const sf::Color s_clrBlankCell;

private:
    sf::RectangleShape m_body;
    bool m_isOn;
};

#endif /* CELL_H */

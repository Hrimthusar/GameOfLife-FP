#ifndef CELL_H // include guard
#define CELL_H

#include <SFML/Graphics.hpp>

class Cell
{
private:

    sf::RectangleShape m_body;
    bool m_isOn;
    bool m_isHovered;

public:
    Cell();
    Cell(sf::RectangleShape body);

    sf::RectangleShape &body();
    const sf::RectangleShape &body() const;

    void setCellColor();

    bool isOn() const;
    void setIsOn(bool isOn);

    bool isHovered() const;
    void setIsHovered(bool isHovered);

    static const sf::Color clrClickedCell;
    static const sf::Color clrClickedHoveredCell;
    static const sf::Color clrHoveredCell;
    static const sf::Color clrBlankCell;
};

#endif /* CELL_H */

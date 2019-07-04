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

    bool isOn() const;
    void setIsOn(bool isOn);

    bool isHovered() const;
    void setIsHovered(bool isHovered);

    void setCellColor();

    static bool applyRules(std::pair<int, bool> element);

    static const sf::Color s_clrClickedCell;
    static const sf::Color s_clrClickedHoveredCell;
    static const sf::Color s_clrHoveredCell;
    static const sf::Color s_clrBlankCell;
};

#endif /* CELL_H */

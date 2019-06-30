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
    void set_isOn(bool isOn);

    bool isHovered() const;
    void set_isHovered(bool isHovered);
};

#endif /* CELL_H */

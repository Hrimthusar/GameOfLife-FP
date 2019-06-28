#ifndef CELL_H // include guard
#define CELL_H

#include <SFML/Graphics.hpp>

// TODO refactor: change to camel case all field variables
class Cell
{
private:
    sf::RectangleShape m_body;
    bool m_is_on;
    bool m_is_hovered;

public:
    Cell();
    Cell(sf::RectangleShape body);

    sf::RectangleShape &body();
    const sf::RectangleShape &body() const;

    bool is_on() const;
    void set_is_on(bool is_on);

    bool is_hovered() const;
    void set_is_hovered(bool is_hovered);
};

#endif /* CELL_H */

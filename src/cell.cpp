
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "cell.hpp"

Cell::Cell(sf::RectangleShape body)
    : m_body(body), m_is_on(false), m_is_hovered(false)
{
}

Cell::Cell()
    : m_body(sf::Vector2f(0, 0)), m_is_on(false), m_is_hovered(false)
{
}

sf::RectangleShape &Cell::body()
{
    return m_body;
}

const sf::RectangleShape &Cell::body() const
{
    return m_body;
}

bool Cell::is_on() const
{
    return m_is_on;
}

void Cell::set_is_on(bool is_on)
{
    m_is_on = is_on;
}

bool Cell::is_hovered() const
{
    return m_is_hovered;
}

void Cell::set_is_hovered(bool is_hovered)
{
    m_is_hovered = is_hovered;
}


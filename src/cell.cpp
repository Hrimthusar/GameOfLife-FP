
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "cell.hpp"

Cell::Cell(sf::RectangleShape body)
    : m_body(body), m_isOn(false), m_isHovered(false)
{
}

Cell::Cell()
    : m_body(sf::Vector2f(0, 0)), m_isOn(false), m_isHovered(false)
{
}

const sf::RectangleShape &Cell::body() const
{
    return m_body;
}

sf::RectangleShape &Cell::body()
{
    return m_body;
}

bool Cell::isOn() const
{
    return m_isOn;
}

void Cell::set_isOn(bool isOn)
{
    m_isOn = isOn;
}

bool Cell::isHovered() const
{
    return m_isHovered;
}

void Cell::set_isHovered(bool isHovered)
{
    m_isHovered = isHovered;
}

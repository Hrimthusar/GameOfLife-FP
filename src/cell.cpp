
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "cell.hpp"

const sf::Color Cell::s_clrClickedCell = sf::Color(0x00, 0x33, 0x66);
const sf::Color Cell::s_clrClickedHoveredCell = sf::Color(0x00, 0x99, 0xFF);
const sf::Color Cell::s_clrHoveredCell = sf::Color(0x00, 0xFF, 0xFF);
const sf::Color Cell::s_clrBlankCell = sf::Color(0xCC, 0xFF, 0xFF);

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

void Cell::setIsOn(bool isOn)
{
    m_isOn = isOn;
}

bool Cell::isHovered() const
{
    return m_isHovered;
}

void Cell::setIsHovered(bool isHovered)
{
    m_isHovered = isHovered;
}

void Cell::setCellColor()
{
    if (isOn() && isHovered())
        m_body.setFillColor(s_clrClickedHoveredCell);
    else if (m_isOn)
        m_body.setFillColor(s_clrClickedCell);
    else if (m_isHovered)
        m_body.setFillColor(s_clrHoveredCell);
    else
        m_body.setFillColor(s_clrBlankCell);
}

// TODO: move rules to seperate functions,
//       apply all rules to pair<int,bool> argument
//       apply all_of function on outputs
bool Cell::applyRules(std::pair<int, bool> element)
{
    auto neighboursCount = element.first;
    auto alive = element.second;

    if (alive && (neighboursCount < 2 || neighboursCount > 3))
    {
        return false;
    }
    else if (!alive && neighboursCount == 3)
    {
        return true;
    }
    return alive;
}


#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "world.hpp"

/* Null, because instance will be initialized on demand. */
World *World::instance = NULL;

World *World::getInstance(unsigned w, unsigned h)
{
  if (instance == NULL)
  {
    instance = new World(w, h);
  }

  return instance;
}

World::World(unsigned w, unsigned h)
// : screenWidth(w), screenHeight(h)
{
  std::cout << w << " " << h << std::endl;
  screenWidth = w;
  screenHeight = h;
}

void World::initGrid(unsigned m, unsigned n)
{
  xCount = m;
  yCount = n;

  unsigned cellSizeX = (screenWidth - cellMargin) / xCount;
  unsigned cellSizeY = (screenHeight - cellMargin) / yCount;

  cellSize = std::min(cellSizeX, cellSizeY) - cellMargin;

  innerWidth = ((cellSize + cellMargin) * xCount) - cellMargin;
  innerHeight = ((cellSize + cellMargin) * yCount) - cellMargin;

  unsigned topPadding = (screenHeight % innerHeight) / 2;
  unsigned leftPadding = (screenWidth % innerWidth) / 2;

  grid.resize(xCount);
  for (unsigned i = 0; i < xCount; ++i)
    grid[i].resize(yCount);

  for (unsigned i = 0; i < xCount; ++i)
  {
    for (unsigned j = 0; j < yCount; ++j)
    {
      grid[i][j].first = sf::RectangleShape(sf::Vector2f(cellSize, cellSize));
      grid[i][j].first.setPosition(leftPadding + i * (cellMargin + cellSize),
                                   topPadding + j * (cellMargin + cellSize));

      if (grid[i][j].second == 0)
        grid[i][j].first.setFillColor(sf::Color::Blue);
      else
        grid[i][j].first.setFillColor(sf::Color::Cyan);
    }
  }
};

void World::handleHover(sf::Event &event)
{
  auto &mouseX = event.mouseMove.x;
  auto &mouseY = event.mouseMove.y;

  //                  TODO: Left padding
  auto x = (mouseX - (screenWidth % innerWidth) / 2) / (cellSize + cellMargin);
  //                  TODO: Top padding
  auto y = (mouseY - (screenHeight % innerHeight) / 2) / (cellSize + cellMargin);

  std::cout << x << "," << y << std::endl;

  for (unsigned i = 0; i < xCount; ++i)
  {
    for (unsigned j = 0; j < yCount; ++j)
    {
      grid[i][j].second = 0;
    }
  }

  if (x >= 0 && x < xCount && y >= 0 && y < yCount)
    grid[x][y].second = 1; // TODO: indikator za hover...
}

// if (event.type == sf::Event::MouseMoved)
// {
//     std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
//     std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
// }

void World::drawGrid(sf::RenderWindow &window)
{
  for (unsigned i = 0; i < xCount; ++i)
  {
    for (unsigned j = 0; j < yCount; ++j)
    {
      if (grid[i][j].second == 0)
        grid[i][j].first.setFillColor(sf::Color::Blue);
      else
        grid[i][j].first.setFillColor(sf::Color::Cyan);
      window.draw(grid[i][j].first);
    }
  }
}
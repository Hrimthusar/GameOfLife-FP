#ifndef GRID_H
#define GRID_H

#include <stdexcept>
#include "cell.hpp"
#include <iostream>

class Grid
{
public:
  /* The iterator */
  class Iterator
  {
  public:
    Iterator(const Grid *grid, int xIndex, int yIndex, int m_xSize);
    const Cell &operator*() const;
    // Cell &operator*();
    Iterator &operator++();
    bool operator!=(const Iterator &other) const;

  private:
    const Grid *m_pGrid;
    int m_xIndex = -1;
    int m_yIndex = -1;
    int m_xSize = 0;
  };

public:
  // constructors
  Grid();
  // explicit Grid(int nSize);

  ~Grid();

  // void insert(const T &value);

  void resizeMatrix(unsigned xCount, unsigned yCount);
  int size() const;
  const Cell &operator[](std::pair<int, int> index) const;
  Cell &operator[](std::pair<int, int> index);

  Iterator begin() const;
  Iterator end() const;

private:
  // std::vector<std::vector<Cell>> *m_pData = nullptr;
  std::vector<std::vector<Cell>> m_pData;

  // Cell *m_pData = nullptr;
  int m_xSize = 0;
  int m_ySize = 0;
};

/*
 * Grid
 * methods
 **/
// Grid::Grid(int nCapacity)
// {
//   m_nCapacity = nCapacity;
//   m_pData = new T[m_nCapacity];
// }

#endif // !GRID_H

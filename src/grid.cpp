#include "grid.hpp"

Grid::Grid()
{
  // m_pData = new std::vector<std::vector<Cell>>;
  std::cout << &m_pData << std::endl;
}

Grid::~Grid()
{
  // delete m_pData;
  m_xSize = 0;
  m_ySize = 0;
}

void Grid::resizeMatrix(unsigned xCount, unsigned yCount)
{
  m_xSize = xCount;
  m_ySize = yCount;

  std::cout << &m_pData << std::endl;
  std::cout << xCount << ", " << yCount << std::endl;

  // m_pData->resize(xCount);
  m_pData.resize(xCount);
  for (unsigned i = 0; i < xCount; ++i)
  {
    std::cout << i << std::endl;

    // (*m_pData)[i].resize(yCount);
    m_pData[i].resize(yCount);
  }
}

int Grid::size() const
{
  return m_xSize * m_ySize;
}

const Cell &Grid::operator[](std::pair<int, int> index) const
{
  // std::cout << "[const]" << std::endl;
  if (index.first >= m_xSize || index.second >= m_ySize)
    throw std::out_of_range("Index out of range");

  return m_pData[index.first][index.second];
}

Cell &Grid::operator[](std::pair<int, int> index)
{
  // std::cout << "[]" << std::endl;
  if (index.first >= m_xSize || index.second >= m_ySize)
    throw std::out_of_range("Index out of range");

  return m_pData[index.first][index.second];
}

Grid::Iterator Grid::begin() const
{
  return Grid::Iterator{this, 0, 0, m_xSize};
}

Grid::Iterator Grid::end() const
{
  return Grid::Iterator{this, 0, m_ySize, m_xSize};
}

/*
 * Iterator methods
 **/
Grid::Iterator::Iterator(const Grid *pGrid, int xIndex, int yIndex, int m_xSize)
    : m_pGrid(pGrid), m_xIndex(xIndex), m_yIndex(yIndex), m_xSize(m_xSize)
{
}

const Cell &Grid::Iterator::operator*() const
{
  std::cout << "deref " << m_xIndex << "," << m_yIndex << std::endl;
  return m_pGrid->operator[](std::make_pair(m_xIndex, m_yIndex));
}

// Cell &Grid::Iterator::operator*()
// {
//   std::cout << "deref" << std::endl;
//   return m_pGrid->operator[](std::make_pair(m_xIndex, m_yIndex));
// }

typename Grid::Iterator &Grid::Iterator::operator++()
{
  if (++m_xIndex >= m_xSize)
  {
    m_xIndex = 0;
    ++m_yIndex;
  }
  std::cout << m_xIndex << "," << m_yIndex << std::endl;
  return *this;
}

bool Grid::Iterator::operator!=(const Grid::Iterator &other) const
{
  return m_xIndex != other.m_xIndex || m_yIndex != other.m_yIndex;
}
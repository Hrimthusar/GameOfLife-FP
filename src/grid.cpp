#include "grid.hpp"

Grid::Grid()
{
    // m_data = new std::vector<std::vector<Cell>>;
    // std::cout << &m_data << std::endl;
}

Grid::~Grid()
{
    // delete m_data;
    m_xSize = 0;
    m_ySize = 0;
}

bool Grid::indicesInBounds(int x, int y)
{
    return (x >= 0 && x < m_xSize && y >= 0 && y < m_ySize);
}

bool Grid::indicesInBounds(std::pair<int, int> indices)
{
    return indicesInBounds(indices.first, indices.second);
}

void Grid::resizeMatrix(unsigned xCount, unsigned yCount)
{
    m_xSize = xCount;
    m_ySize = yCount;

    // std::cout << &m_data << std::endl;
    // std::cout << xCount << ", " << yCount << std::endl;

    // m_data->resize(xCount);
    m_data.resize(xCount);
    for (unsigned i = 0; i < xCount; ++i)
    {
        // std::cout << i << std::endl;

        // (*m_data)[i].resize(yCount);
        m_data[i].resize(yCount);
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

    return m_data[index.first][index.second];
}

Cell &Grid::operator[](std::pair<int, int> index)
{
    // std::cout << "[]" << std::endl;
    if (index.first >= m_xSize || index.second >= m_ySize)
        throw std::out_of_range("Index out of range");

    return m_data[index.first][index.second];
}

Grid::Iterator Grid::begin()
{
    return Grid::Iterator{this, 0, 0, m_xSize};
}

Grid::Iterator Grid::end()
{
    return Grid::Iterator{this, 0, m_ySize, m_xSize};
}

/*
 * Iterator methods
 **/
Grid::Iterator::Iterator(Grid *pGrid, int xIndex, int yIndex, int m_xSize)
    : m_pGrid(pGrid), m_xIndex(xIndex), m_yIndex(yIndex), m_xSize(m_xSize)
{
}

const Cell &Grid::Iterator::operator*() const
{
    // std::cout << "deref " << m_xIndex << "," << m_yIndex << std::endl;
    return m_pGrid->operator[](std::make_pair(m_xIndex, m_yIndex));
}


Cell& Grid::Iterator::operator*()
{
    // std::cout << "derefNonConst" << std::endl;
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
    // std::cout << m_xIndex << "," << m_yIndex << std::endl;
    return *this;
}

bool Grid::Iterator::operator!=(const Grid::Iterator &other) const
{
    return m_xIndex != other.m_xIndex || m_yIndex != other.m_yIndex;
}

std::pair<int, int> Grid::Iterator::getIndices() const
{
    return std::make_pair(m_xIndex, m_yIndex);
}


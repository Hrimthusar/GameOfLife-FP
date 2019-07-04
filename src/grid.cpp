#include "grid.hpp"
#include <range/v3/view.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/algorithm/count_if.hpp>

using namespace ranges::v3;


Grid::Grid()
{
}

Grid::~Grid()
{
    m_xSize = 0;
    m_ySize = 0;
}

std::vector<Cell> Grid::asRange() const
{
    return m_data | view::join;
}

int Grid::countNeighbours(ranges::common_tuple<int, int> indexedCell) const
{
    int i = std::get<0>(indexedCell);
    int j = std::get<1>(indexedCell);

    static std::vector<int> step{-1, 0, 1};
    static auto steps = view::cartesian_product(step, step);

    return count_if(steps, [&](auto s)
        {
            int i_step = std::get<0>(s);
            int j_step = std::get<1>(s);

            return this->indicesInBounds(i_step + i, j_step + j)
                    && (i_step != 0 || j_step != 0)
                    && (*this)[std::make_pair(i_step + i, j_step + j)].isOn();
        });
}

bool Grid::indicesInBounds(int x, int y) const
{
    return (x >= 0 && x < m_xSize && y >= 0 && y < m_ySize);
}

bool Grid::indicesInBounds(std::pair<int, int> indices) const
{
    return indicesInBounds(indices.first, indices.second);
}

void Grid::resizeMatrix(unsigned xCount, unsigned yCount)
{
    m_xSize = xCount;
    m_ySize = yCount;

    m_data.resize(xCount);
    for (unsigned i = 0; i < xCount; ++i)
    {
        m_data[i].resize(yCount);
    }
}

int Grid::size() const
{
    return m_xSize * m_ySize;
}

const Cell &Grid::operator[](std::pair<int, int> index) const
{
    if (index.first >= m_xSize || index.second >= m_ySize)
        throw std::out_of_range("Index out of range");

    return m_data[index.first][index.second];
}

Cell &Grid::operator[](std::pair<int, int> index)
{
    if (index.first >= m_xSize || index.second >= m_ySize)
        throw std::out_of_range("Index out of range");

    return m_data[index.first][index.second];
}

Grid::Iterator Grid::begin()
{
    return Grid::Iterator{this, 0, 0, m_ySize};
}

Grid::Iterator Grid::end()
{
    return Grid::Iterator{this, m_xSize, 0, m_ySize};
}

/*
 * Iterator methods
 **/
Grid::Iterator::Iterator(Grid *pGrid, int xIndex, int yIndex, int ySize)
    : m_pGrid(pGrid), m_xIndex(xIndex), m_yIndex(yIndex), m_ySize(ySize)
{
}

const Cell &Grid::Iterator::operator*() const
{
    return m_pGrid->operator[](std::make_pair(m_xIndex, m_yIndex));
}


Cell& Grid::Iterator::operator*()
{
    return m_pGrid->operator[](std::make_pair(m_xIndex, m_yIndex));
}

typename Grid::Iterator &Grid::Iterator::operator++()
{
    if (++m_yIndex >= m_ySize)
    {
        m_yIndex = 0;
        ++m_xIndex;
    }
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


#ifndef GRID_H
#define GRID_H

#include <stdexcept>
#include "cell.hpp"
#include <iostream>
#include <range/v3/view.hpp>

class Grid
{
public:
    class Iterator
    {
    public:
        Iterator(Grid *grid, int xIndex, int yIndex, int m_ySize);

        const Cell &operator*() const;
        Cell &operator*();

        Iterator &operator++();
        bool operator!=(const Iterator &other) const;

        std::pair<int, int> getIndices() const;

    private:
        Grid *m_pGrid;
        int m_xIndex = -1;
        int m_yIndex = -1;
        int m_ySize = 0;
    };

public:
    Grid();
    ~Grid();

    std::vector<Cell> asRange() const;

    int countNeighbours(ranges::common_tuple<int, int> indexedCell) const;
    bool indicesInBounds(int x, int y) const;
    bool indicesInBounds(std::pair<int, int> indices) const;

    void resizeMatrix(unsigned xCount, unsigned yCount);
    int size() const;
    const Cell &operator[](std::pair<int, int> index) const;
    Cell &operator[](std::pair<int, int> index);

    Iterator begin();
    Iterator end();

private:
    std::vector<std::vector<Cell>> m_data;

    int m_xSize = 0;
    int m_ySize = 0;
};

#endif // !GRID_H

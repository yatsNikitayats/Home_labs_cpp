#pragma once
#include <memory>
#include "Cell.h"
#include "Bonus.h"

class Board {
public:
    static constexpr int SIZE = 14;

    Board();
    ~Board() = default;

    Cell* getCell(int x, int y) const;
    void setCell(int x, int y, std::unique_ptr<Cell> cell);

    
    std::unique_ptr<Cell> releaseCell(int x, int y);

    void swapCells(int x1, int y1, int x2, int y2);

   
    bool isEmpty(int x, int y) const;
    bool hasBonusAt(int x, int y) const;
    int getSize() const;

    
    void clearCell(int x, int y);

private:
    std::unique_ptr<Cell> grid[SIZE][SIZE];
};




#include "Board.h"
#include "CellFactory.h"
#include "Utils.h"

Board::Board() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = nullptr;
        }
    }
}

Cell* Board::getCell(int x, int y) const {
    return grid[y][x].get();
}

void Board::setCell(int x, int y, std::unique_ptr<Cell> cell) {
    grid[y][x] = std::move(cell);
}

std::unique_ptr<Cell> Board::releaseCell(int x, int y) {
    return std::move(grid[y][x]);
}

void Board::swapCells(int x1, int y1, int x2, int y2) {
    std::swap(grid[y1][x1], grid[y2][x2]);
}

bool Board::isEmpty(int x, int y) const {
    return grid[y][x] == nullptr;
}

bool Board::hasBonusAt(int x, int y) const {
    return grid[y][x] && grid[y][x]->isBonus();
}

int Board::getSize() const {
    return SIZE;
}

void Board::clearCell(int x, int y) {
    grid[y][x].reset();
}




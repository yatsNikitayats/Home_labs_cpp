#pragma once
#include "Board.h"

class BoardInitializer {
public:
    static void initRandom(Board& board);

private:
    static int countClusterSize(const Board& board, int x, int y, int color);
};






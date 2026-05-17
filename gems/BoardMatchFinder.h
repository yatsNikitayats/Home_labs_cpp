#pragma once
#include "Board.h"
#include <vector>

class BoardMatchFinder {
public:
    struct Match {
        std::vector<std::pair<int, int>> cells;
        int color;
    };

    static std::vector<Match> findAllMatches(Board& board);

    static bool hasAnyMatch(Board& board);

private:
    static void dfs(Board& board, int x, int y, int color,
        bool visited[Board::SIZE][Board::SIZE],
        std::vector<std::pair<int, int>>& component);
};


#include "BoardInitializer.h"
#include "Utils.h"

int BoardInitializer::countClusterSize(const Board& board, int x, int y, int color) {
    bool visited[Board::SIZE][Board::SIZE] = {};
    std::vector<std::pair<int, int>> stack = { {x, y} };
    int size = 0;

    while (!stack.empty()) {
        auto [cx, cy] = stack.back();
        stack.pop_back();

        if (!inBounds(cx, cy, Board::SIZE)) continue;
        if (visited[cy][cx]) continue;
        if (board.getCell(cx, cy) != color) continue;

        visited[cy][cx] = true;
        size++;

        stack.push_back({ cx + 1, cy });
        stack.push_back({ cx - 1, cy });
        stack.push_back({ cx, cy + 1 });
        stack.push_back({ cx, cy - 1 });
    }

    return size;
}

void BoardInitializer::initRandom(Board& board) {
    for (int i = 0; i < Board::SIZE; i++) {
        for (int j = 0; j < Board::SIZE; j++) {
            board.setCell(j, i, -1);
        }
    }

    for (int i = 0; i < Board::SIZE; i++) {
        for (int j = 0; j < Board::SIZE; j++) {
            int v;
            do {
                v = rnd(0, 4);
                board.setCell(j, i, v);
            } while (countClusterSize(board, j, i, v) >= 3);
        }
    }
}


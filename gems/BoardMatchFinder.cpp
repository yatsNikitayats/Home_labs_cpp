#include "BoardMatchFinder.h"
#include "Utils.h"

void BoardMatchFinder::dfs(Board& board, int x, int y, int color,
    bool visited[Board::SIZE][Board::SIZE],
    std::vector<std::pair<int, int>>& component) {
    if (!inBounds(x, y, Board::SIZE)) return;
    if (visited[y][x]) return;
    if (board.getFieldAt(x, y) != color) return;
    if (board.isEmpty(x, y)) return;

    visited[y][x] = true;
    component.push_back({ x, y });

    dfs(board, x + 1, y, color, visited, component);
    dfs(board, x - 1, y, color, visited, component);
    dfs(board, x, y + 1, color, visited, component);
    dfs(board, x, y - 1, color, visited, component);
}

std::vector<BoardMatchFinder::Match> BoardMatchFinder::findAllMatches(Board& board) {
    bool visited[Board::SIZE][Board::SIZE] = {};
    std::vector<Match> matches;

    for (int y = 0; y < Board::SIZE; y++) {
        for (int x = 0; x < Board::SIZE; x++) {
            if (visited[y][x]) continue;
            if (board.isEmpty(x, y)) continue;

            std::vector<std::pair<int, int>> component;
            dfs(board, x, y, board.getFieldAt(x, y), visited, component);

            if (component.size() >= 3) {
                matches.push_back({ component, board.getFieldAt(x, y) });
            }
        }
    }

    return matches;
}

bool BoardMatchFinder::hasAnyMatch(Board& board) {
    return !findAllMatches(board).empty();
}


#include "BonusManager.h"
#include "Utils.h"
#include <algorithm>

bool BonusManager::isValidSpawnPoint(Board& board, int x, int y,
    const bool toDelete[Board::SIZE][Board::SIZE]) {
    if (!inBounds(x, y, Board::SIZE)) return false;
    if (toDelete[y][x]) return false;
    if (board.isEmpty(x, y)) return false;
    if (board.hasBonusAt(x, y)) return false;
    return true;
}


bool BonusManager::trySpawnBonus(Board& board, int centerX, int centerY,
    int originColor,
    const bool toDelete[Board::SIZE][Board::SIZE],
    std::vector<DropEffect>& dropEffects) {  

    std::vector<std::pair<int, int>> spawnPoints;

    for (int dy = -3; dy <= 3; dy++) {
        for (int dx = -3; dx <= 3; dx++) {
            int nx = centerX + dx;
            int ny = centerY + dy;

            if (manhattan(centerX, centerY, nx, ny) > 3) continue;
            if (!isValidSpawnPoint(board, nx, ny, toDelete)) continue;

            spawnPoints.push_back({ nx, ny });
        }
    }

    if (spawnPoints.empty()) return false;

    auto [bx, by] = spawnPoints[rnd(0, spawnPoints.size() - 1)];
    BonusType newType = (rnd(0, 1) == 0) ? BonusType::COLORIZE : BonusType::BOMB;

    Bonus newBonus;
    newBonus.type = newType;
    newBonus.originColor = originColor;
    board.setBonus(bx, by, newBonus);

   
    dropEffects.push_back({
        bx * 64.0f + 32.0f,
        by * 64.0f + 32.0f,
        1.2f,  
        newType
        });

    return true;
}

void BonusManager::applyColorizeBonus(Board& board, int x, int y, int originColor) {
  
    if (!board.isEmpty(x, y)) {
        board.setCell(x, y, originColor);
    }

    
    std::vector<std::pair<int, int>> nonAdj;
    for (int dy = -3; dy <= 3; dy++) {
        for (int dx = -3; dx <= 3; dx++) {
            int nx = x + dx;
            int ny = y + dy;

            if (!inBounds(nx, ny, Board::SIZE)) continue;
            if (manhattan(x, y, nx, ny) > 3) continue;
            if (manhattan(x, y, nx, ny) <= 1) continue;
            if (board.isEmpty(nx, ny)) continue;

            nonAdj.push_back({ nx, ny });
        }
    }

    std::shuffle(nonAdj.begin(), nonAdj.end(), gen);

    std::vector<std::pair<int, int>> selected;

    for (auto [tx, ty] : nonAdj) {
        bool ok = true;

        for (auto [sx, sy] : selected) {
            if (manhattan(tx, ty, sx, sy) <= 1) {
                ok = false;
                break;
            }
        }

        if (!ok) continue;

        selected.push_back({ tx, ty });

        if (selected.size() >= 2)
            break;
    }

    for (auto [tx, ty] : selected) {
        board.setCell(tx, ty, originColor);
    }
}

void BonusManager::applyBombBonus(Board& board, int x, int y,
    std::vector<DropEffect>& dropEffects) {
    std::vector<std::pair<int, int>> all;
    all.push_back({ x, y });

    for (int i = 0; i < Board::SIZE; i++) {
        for (int j = 0; j < Board::SIZE; j++) {
            if (!board.isEmpty(j, i) && !(j == x && i == y)) {
                all.push_back({ j, i });
            }
        }
    }

    std::shuffle(all.begin(), all.end(), gen);

    std::vector<std::pair<int, int>> toDestroy;
    toDestroy.push_back({ x, y });

    for (auto [tx, ty] : all) {
        if (toDestroy.size() >= 5) break;

        bool dup = false;
        for (auto [cx, cy] : toDestroy) {
            if (cx == tx && cy == ty) {
                dup = true;
                break;
            }
        }
        if (!dup) toDestroy.push_back({ tx, ty });
    }

    for (auto [tx, ty] : toDestroy) {
        board.setCell(tx, ty, -1);
        board.clearBonus(tx, ty);
    }
}

void BonusManager::activateBonus(Board& board, int x, int y,
    std::vector<DropEffect>& dropEffects) {
    if (!inBounds(x, y, Board::SIZE)) return;
    if (!board.hasBonusAt(x, y)) return;

    Bonus bonus = board.getBonus(x, y);
    BonusType type = bonus.type;
    int originColor = bonus.originColor;

    board.clearBonus(x, y);

    if (type == BonusType::COLORIZE) {
        applyColorizeBonus(board, x, y, originColor);
    }
    else if (type == BonusType::BOMB) {
        applyBombBonus(board, x, y, dropEffects);
    }
}

void BonusManager::clearBonusesAt(Board& board,
    const std::vector<std::pair<int, int>>& cells) {
    for (auto [x, y] : cells) {
        board.clearBonus(x, y);
    }
}


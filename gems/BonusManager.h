#pragma once
#include "Board.h"
#include "Bonus.h"
#include <vector>

class BonusManager {
public:
    
    static bool trySpawnBonus(Board& board, int centerX, int centerY,
        int originColor,
        const bool toDelete[Board::SIZE][Board::SIZE],
        std::vector<DropEffect>& dropEffects);  
 
    static void activateBonus(Board& board, int x, int y,
        std::vector<DropEffect>& dropEffects);

    
    static void clearBonusesAt(Board& board,
        const std::vector<std::pair<int, int>>& cells);

    
    static bool isValidSpawnPoint(Board& board, int x, int y,
        const bool toDelete[Board::SIZE][Board::SIZE]);

private:
    static void applyColorizeBonus(Board& board, int x, int y, int originColor);
    static void applyBombBonus(Board& board, int x, int y,
        std::vector<DropEffect>& dropEffects);
};


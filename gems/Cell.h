#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Board;  
struct DropEffect;

class Cell {
public:
    virtual ~Cell() = default;

    virtual int getColorValue() const = 0;           
    virtual bool isBonus() const { return false; }
    virtual sf::Color getRenderColor() const = 0;
    virtual void activate(Board& board, int x, int y,
        std::vector<DropEffect>& dropEffects) {
    }
};






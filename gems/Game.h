#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Bonus.h"

class Game {
public:
    Game();
    void run();
private:
    void update(float dt);
    void render();
    void handleMouseClick(int x, int y);

    sf::RenderWindow window;
    Board board;
    std::vector<DropEffect> dropEffects;

    bool hasFirst;
    int fx, fy;
    float selectionTimer;

    sf::RectangleShape cell;
    sf::RectangleShape selectionRect;
    sf::CircleShape bonusMarker;
    sf::Clock clock;
};




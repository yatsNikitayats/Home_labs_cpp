#include "Game.h"
#include "BoardInitializer.h"
#include "BoardGravity.h"
#include "BoardResolver.h"
#include "Utils.h"
#include <iostream>

Game::Game()
    : window(sf::VideoMode({ Board::SIZE * 64, Board::SIZE * 64 }), "GEMS - Match3")
    , hasFirst(false)
    , fx(-1), fy(-1)
    , selectionTimer(0.0f)
    , cell(sf::Vector2f(62, 62))
    , selectionRect(sf::Vector2f(62, 62))
    , bonusMarker(8.f) {

    BoardInitializer::initRandom(board);
    selectionRect.setFillColor(sf::Color::Transparent);
    selectionRect.setOutlineThickness(4);
    selectionRect.setOutlineColor(sf::Color::Yellow);
    bonusMarker.setOutlineThickness(2);
    bonusMarker.setOutlineColor(sf::Color::White);
}

void Game::handleMouseClick(int x, int y) {
    if (!inBounds(x, y, board.getSize())) return;

    if (!hasFirst) {
        fx = x; fy = y;
        hasFirst = true;
        selectionTimer = 0.5f;
    }
    else {
        if (fx == x && fy == y) {
            hasFirst = false;
            selectionTimer = 0;
            return;
        }
        if (abs(fx - x) + abs(fy - y) == 1) {
            board.swapCells(fx, fy, x, y);
            if (BoardResolver::resolveBoard(board, dropEffects, true)) {
                BoardResolver::stabilize(board, dropEffects);
            }
            else {
                board.swapCells(fx, fy, x, y);
            }
        }
        hasFirst = false;
        fx = fy = -1;
        selectionTimer = 0;
    }
}

void Game::update(float dt) {
    if (selectionTimer > 0) selectionTimer -= dt;
    for (auto it = dropEffects.begin(); it != dropEffects.end();) {
        it->life -= dt;
        if (it->life <= 0) it = dropEffects.erase(it);
        else ++it;
    }
}

void Game::render() {
    window.clear(sf::Color(20, 20, 20));
    for (int i = 0; i < board.getSize(); i++) {
        for (int j = 0; j < board.getSize(); j++) {
            cell.setPosition(sf::Vector2f(j * 64 + 1, i * 64 + 1));
            Cell* c = board.getCell(j, i);
            if (c) {
                cell.setFillColor(c->getRenderColor());
            }
            else {
                cell.setFillColor(sf::Color(30, 30, 30));
            }
            window.draw(cell);

            if (hasFirst && fx == j && fy == i && selectionTimer > 0) {
                selectionRect.setPosition(sf::Vector2f(j * 64 + 1, i * 64 + 1));
                float alpha = 0.5f + 0.5f * std::sin(selectionTimer * 25.0f);
                selectionRect.setOutlineColor(sf::Color(255, 255, 0, static_cast<std::uint8_t>(255 * alpha)));
                window.draw(selectionRect);
            }
        }
    }

    for (const auto& eff : dropEffects) {
        float radius = 15.f * (1.f - eff.life / 1.2f);
        sf::CircleShape effectCircle(radius);
        effectCircle.setPosition(sf::Vector2f(eff.x - radius, eff.y - radius));
        sf::Color col = (eff.type == BonusType::COLORIZE) ? sf::Color(0, 255, 255, 180) : sf::Color(50, 50, 50, 180);
        effectCircle.setFillColor(col);
        effectCircle.setOutlineThickness(2);
        effectCircle.setOutlineColor(sf::Color::White);
        window.draw(effectCircle);
    }
    window.display();
}

void Game::run() {
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            else if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseEvent->button == sf::Mouse::Button::Left) {
                    int x = mouseEvent->position.x / 64;
                    int y = mouseEvent->position.y / 64;
                    handleMouseClick(x, y);
                }
            }
        }
        update(dt);
        render();
    }
}






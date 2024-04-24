// Level.cpp
#include "Level.h"

Level::Level(N5110& lcd)
    : lcd(lcd), boss(&lcd, 42, 0, 20, 2) {}

void Level::load() {
    enemies.clear();
    // Spawn regular enemies
    enemies.emplace_back(&lcd, 10, 24, 5, 1);
    enemies.emplace_back(&lcd, 30, 24, 5, 1);
    enemies.emplace_back(&lcd, 50, 24, 5, 1);
    enemies.emplace_back(&lcd, 70, 24, 5, 1);
}

void Level::update() {
    for (auto& enemy : enemies) {
        if (!enemy.isDead()) {
            enemy.update();
            enemy.draw();
        }
    }

    if (!boss.isDead()) {
        boss.update();
        boss.draw();
    }
}
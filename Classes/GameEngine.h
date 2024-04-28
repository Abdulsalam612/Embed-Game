#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "mbed.h"
#include "Enemy.h"
#include "Joystick.h"
#include "Bitmap.h"
#include "Projectile.h"
#include "Character.h"
#include "MainMenu.h"
#include "Level.h"

#include <vector>

#include "N5110.h"


class GameEngine {
public:
    GameEngine(N5110& lcd, Joystick& joystick1, Joystick& joystick2, DigitalIn& button1, DigitalIn& button2);
    bool run();

private:
    void init();
    void refreshDisplay();
    void handleProjectiles();
    void handleEnemyCollision();
    void printEnemyHp();
    void showVictoryScreen();

    // Hardware components
    N5110& lcd;
    Joystick& joystick1;
    Joystick& joystick2;
    DigitalIn& button1;
    DigitalIn& button2;

    // Game entities
    Character character;
    std::vector<Projectile> projectiles;
    Enemy enemy;
    Level currentLevel;
};

#endif
// Level.h
#ifndef LEVEL_H
#define LEVEL_H

#include "mbed.h"
#include "N5110.h"
#include "Enemy.h"
#include <vector>

class Level {
public:
    Level(N5110& lcd, DigitalIn& button);
    void load();
    void update();
    void showBossDialogue();

private:
    N5110& lcd;
    DigitalIn& button;
    std::vector<Enemy> enemies;
    Enemy boss;
};

#endif
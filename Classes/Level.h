// Level.h
#ifndef LEVEL_H
#define LEVEL_H

#include "mbed.h"
#include "N5110.h"
#include "Enemy.h"
#include <vector>

class Level {
public:
    Level(N5110& lcd);
    void load();
    void update();

private:
    N5110& lcd;
    std::vector<Enemy> enemies;
    Enemy boss;
};

#endif
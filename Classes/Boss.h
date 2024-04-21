#ifndef BOSS_H
#define BOSS_H

#include "mbed.h"
#include "N5110.h"

class Boss {
public:
    Boss(N5110* lcd, float initialX, float initialY, int initialHp, int initialDamage);
    void update();
    void draw();
    void takeDamage();
    bool isDead();
    void setDead(bool value);

    float x_pos, y_pos;
    int hp;
    int damage;
    int getHp() const;

private:
    N5110* lcd;
    int width;
    int height;
    int direction;
    bool dead;
};

#endif
#ifndef Enemy_H
#define Enemy_H

#include "mbed.h"
#include "N5110.h"

class Enemy {
public:
    Enemy(N5110* lcd, float initialX, float initialY, int initialHp, int initialDamage, float initialSpeed, float dx, float dy);
    void update();
    void draw() const;
    void takeDamage();
    bool isDead() const;
    void setDead(bool value);
    // ...
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    
    

    float x_pos, y_pos;
    int hp;
    int damage;
    int getHp() const;

    

private:
    N5110* lcd;
    int width;
    int height;
    bool dead;
    float direction_x;
    float direction_y;
    float speed;
};

#endif
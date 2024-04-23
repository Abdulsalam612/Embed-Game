#ifndef CHARACTER_H
#define CHARACTER_H

#include "Joystick.h"
#include "Projectile.h"
#include <vector>

class Character {
public:
    Character(float initialX, float initialY, float groundLvl, int initialHp);

    void updatePosition(Joystick& joystick);
    void updateShootingDirection(Joystick& joystick, std::vector<Projectile>& projectiles);
    void applyGravity();
    void jump(bool buttonPressed);
    void boundaryCheck();
    void takeDamage(int damage);
    bool isDead() const;

    float x_pos, y_pos;
    float velocity_y;
    bool buttonReleased;
    int currentSprite;
    int frameCount;
    int idleFrame;
    int hp;

private:
    float groundLevel;
    float gravity;
};

#endif

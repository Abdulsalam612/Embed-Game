#include "Character.h"
#include "mbed.h" // Include if not already included elsewhere in your project

Character::Character(float initialX, float initialY, float groundLvl, int initialHp)
: x_pos(initialX), y_pos(initialY), groundLevel(groundLvl), velocity_y(0), gravity(0.9), buttonReleased(true), currentSprite(0), frameCount(0), idleFrame(0), hp(initialHp) {}

void Character::updatePosition(Joystick& joystick) {
    Direction dir = joystick.get_direction();
    bool moved = false;

    if (dir == N) {
        y_pos--;
        moved = true;
    } else if (dir == S) {
        y_pos++;
        moved = true;
    } else if (dir == E) {
        x_pos++;
        moved = true;
    } else if (dir == W) {
        x_pos--;
        moved = true;
    } else if (dir == NE) {
        y_pos--;
        x_pos++;
        moved = true;
    } else if (dir == NW) {
        y_pos--;
        x_pos--;
        moved = true;
    } else if (dir == SE) {
        y_pos++;
        x_pos++;
        moved = true;
    } else if (dir == SW) {
        y_pos++;
        x_pos--;
        moved = true;
    }

    if (moved) {
        frameCount++;
        if (frameCount >= 6) {  // Change sprite every 10 frames
            currentSprite = !currentSprite;
            frameCount = 0;
        }
    }
}

void Character::updateShootingDirection(Joystick& joystick, std::vector<Projectile>& projectiles) {
    float dx = 0, dy = 0;
    Direction dir = joystick.get_direction();
    float startX = x_pos + 2;
    float startY = y_pos + 3.5;

    if (dir == N) {
        dy = -1;
        startY = y_pos;
    } else if (dir == S) {
        dy = 1;
        startY = y_pos + 7;
    } else if (dir == E) {
        dx = 1;
        startX = x_pos + 4;
    } else if (dir == W) {
        dx = -1;
        startX = x_pos;
    } else if (dir == NE) {
        dx = 1;
        dy = -1;
        startX = x_pos + 4;
        startY = y_pos;
    } else if (dir == NW) {
        dx = -1;
        dy = -1;
        startX = x_pos;
        startY = y_pos;
    } else if (dir == SE) {
        dx = 1;
        dy = 1;
        startX = x_pos + 4;
        startY = y_pos + 7;
    } else if (dir == SW) {
        dx = -1;
        dy = 1;
        startX = x_pos;
        startY = y_pos + 7;
    }

    projectiles.push_back(Projectile(startX, startY, dx, dy));
}

void Character::applyGravity() {
    velocity_y += gravity;
    y_pos += velocity_y;
    y_pos = std::min(y_pos, groundLevel);
    if (y_pos >= groundLevel) {
        y_pos = groundLevel;
        velocity_y = 0;
    }
}

void Character::jump(bool buttonPressed) {
    if (buttonPressed && buttonReleased) {
        velocity_y = -5;
        buttonReleased = false;
    } else if (!buttonPressed) {
        buttonReleased = true;
    }
}

void Character::boundaryCheck() {
    if (x_pos < 1) x_pos = 1;
    else if (x_pos > 81) x_pos = 81;

    if (y_pos < 1) y_pos = 1;
    else if (y_pos > groundLevel) y_pos = groundLevel;
}

void Character::takeDamage(int damage) {
    hp -= damage;
    if (hp < 0) {
        hp = 0;
    }
}

bool Character::isDead() const {
    return hp <= 0;
}

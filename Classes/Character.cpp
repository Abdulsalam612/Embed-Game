#include "Character.h"
#include "mbed.h" // Include if not already included elsewhere in your project

Character::Character(float initialX, float initialY, float groundLvl, int initialHp)
    : x_pos(initialX), y_pos(initialY), groundLevel(groundLvl), velocity_y(0), gravity(0.6),
      buttonReleased(true), currentSprite(0), frameCount(0), idleFrame(0), hp(initialHp),
      shootingTimer() {
    shootingTimer.start();
}

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
    float startX = x_pos;
    float startY = y_pos;

    if (dir == N) {
        dy = -1;
        startX += 5; // Adjust the x-position to shoot from the top of the character's head
        startY -= 1; // Adjust the y-position to shoot from above the character's head
    } else if (dir == S) {
        dy = 1;
        startX += 5; // Adjust the x-position to shoot from the bottom of the character's head
        startY += 13; // Adjust the y-position to shoot from below the character's feet
    } else if (dir == E) {
        dx = 1;
        startX += 11; // Adjust the x-position to shoot from the right side of the character
        startY += 6; // Adjust the y-position to shoot from the middle of the character's body
    } else if (dir == W) {
        dx = -1;
        startX -= 1; // Adjust the x-position to shoot from the left side of the character
        startY += 6; // Adjust the y-position to shoot from the middle of the character's body
    } else if (dir == NE) {
        dx = 1;
        dy = -1;
        startX += 7; // Adjust the x-position to shoot from the top-right corner of the character
        startY -= 1; // Adjust the y-position to shoot from above the character's head
    } else if (dir == NW) {
        dx = -1;
        dy = -1;
        startX -= -3; // Adjust the x-position to shoot from the top-left corner of the character
        startY -= 1; // Adjust the y-position to shoot from above the character's head
    } else if (dir == SE) {
        dx = 1;
        dy = 1;
        startX += 7; // Adjust the x-position to shoot from the bottom-right corner of the character
        startY += 13; // Adjust the y-position to shoot from below the character's feet
    } else if (dir == SW) {
        dx = -1;
        dy = 1;
        startX -= -3; // Adjust the x-position to shoot from the bottom-left corner of the character
        startY += 13; // Adjust the y-position to shoot from below the character's feet
    }

    if (dx != 0 || dy != 0) {
        if (shootingTimer.elapsed_time() >= std::chrono::milliseconds(SHOOTING_COOLDOWN)) {
            projectiles.push_back(Projectile(startX, startY, dx, dy));
            shootingTimer.reset();
        }
    }
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
        velocity_y = -4.5;
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

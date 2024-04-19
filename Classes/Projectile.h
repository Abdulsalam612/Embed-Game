#ifndef PROJECTILE_H
#define PROJECTILE_H

struct Projectile {
    float x, y;   // Position of the projectile
    float dx, dy; // Direction of movement

    // Initialize a projectile with position and direction
    Projectile(float posX, float posY, float dirX, float dirY)
        : x(posX), y(posY), dx(dirX), dy(dirY) {}

    // Update the position of the projectile
    void update() {
        x += dx;
        y += dy;
    }
};

#endif

#ifndef PROJECTILE_H
#define PROJECTILE_H


struct Projectile {
    float x, y;   // Position of the projectile
    float dx, dy; // Direction of movement

    // Initialize a projectile with position and direction
    Projectile(float posX, float posY, float dirX, float dirY)
        : x(posX), y(posY), dx(dirX * 1.5), dy(dirY * 1.5) {} // Increase the speed by multiplying dx and dy by a factor (e.g., 3)

    // Update the position of the projectile
    void update() {
        x += dx;
        y += dy;
    }
};

#endif

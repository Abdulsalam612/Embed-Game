#include "Enemy.h"
#include "boss.h"

Enemy::Enemy(N5110* lcd, float initialX, float initialY, int initialHp, int initialDamage)
    : lcd(lcd), x_pos(initialX), y_pos(initialY), hp(initialHp), damage(initialDamage),
      width(10), height(10), direction_x(1), direction_y(1), speed(0.5), dead(false) {}

void Enemy::update() {
    if (!dead) {
        x_pos += direction_x * speed;
        y_pos += direction_y * speed;

        if (x_pos <= 0 || x_pos >= 84 - width) {
            direction_x *= -1;
        }
        if (y_pos <= 0 || y_pos >= 48 - height) {
            direction_y *= -1;
        }
    }
}

int Enemy::getHp() const {
    return hp;
}

void Enemy::draw() const {
    if (!dead) {
        lcd->drawSprite(x_pos, y_pos, boss_width, boss_height, (int *)boss);
    }
}

void Enemy::takeDamage() {
    hp--;
    // Indicate that the enemy is hit (e.g., by changing color or displaying an effect)
    lcd->setPixel(x_pos + width / 2, y_pos + height / 2, 1);
    lcd->refresh();
    ThisThread::sleep_for(100ms);
    lcd->setPixel(x_pos + width / 2, y_pos + height / 2, 0);
    lcd->refresh();
}

bool Enemy::isDead() const {
    return dead;
}

void Enemy::setDead(bool value) {
    dead = value;
}

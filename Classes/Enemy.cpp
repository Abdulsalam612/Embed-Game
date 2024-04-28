#include "Enemy.h"
#include "boss.h"

Enemy::Enemy(N5110* lcd, float initialX, float initialY, int initialHp, int initialDamage)
    : lcd(lcd), x_pos(initialX), y_pos(initialY), hp(initialHp), damage(initialDamage),
      width(10), height(10), direction(1), dead(false) {}

void Enemy::update() {
    if (!dead) {
        x_pos += direction;

        if (x_pos <= 0 || x_pos >= 84 - width) {
            direction *= -1;
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
}

bool Enemy::isDead() const {
    return dead;
}

void Enemy::setDead(bool value) {
    dead = value;
}

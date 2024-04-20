#include "Boss.h"

Boss::Boss(N5110* lcd, float initialX, float initialY, int initialHp, int initialDamage)
    : lcd(lcd), x_pos(initialX), y_pos(initialY), hp(initialHp), damage(initialDamage),
      width(10), height(10), direction(1) {}

void Boss::update() {
    x_pos += direction;

    if (x_pos <= 0 || x_pos >= 84 - width) {
        direction *= -1;
    }
}

void Boss::draw() {
    lcd->drawRect(x_pos, y_pos, width, height, FILL_BLACK);
}

void Boss::takeDamage() {
    hp--;
}

bool Boss::isDead() {
    return hp <= 0;
}
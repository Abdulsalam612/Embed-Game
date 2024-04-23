#include "Boss.h"
#include "boss1.h"

Boss::Boss(N5110* lcd, float initialX, float initialY, int initialHp, int initialDamage)
    : lcd(lcd), x_pos(initialX), y_pos(initialY), hp(initialHp), damage(initialDamage),
      width(10), height(10), direction(1), dead(false) {}

void Boss::update() {
    if (!dead) {
        x_pos += direction;

        if (x_pos <= 0 || x_pos >= 84 - width) {
            direction *= -1;
        }
    }
}

int Boss::getHp() const {
    return hp;
}

void Boss::draw() {
    if (!dead) {
        lcd->drawSprite(x_pos, y_pos, boss1_width, boss1_height, (int *)boss1);
    }
}

void Boss::takeDamage() {
    hp--;
}

bool Boss::isDead() {
    return dead;
}

void Boss::setDead(bool value) {
    dead = value;
}
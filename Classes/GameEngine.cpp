#include "GameEngine.h"
#include "Bitmap.h"
#include "test.h"

GameEngine::GameEngine(N5110& lcd, Joystick& joystick1, Joystick& joystick2, DigitalIn& button1, DigitalIn& button2)
    : lcd(lcd),  joystick1(joystick1), joystick2(joystick2), button1(button1), button2(button2),
      character(42, 24, 40), boss(&lcd, 42, 5, 10, 2) // Example initial positions, ground level, and boss parameters
{
}

void GameEngine::init() {
    lcd.init(LPH7366_1);
    lcd.setContrast(0.6);
    lcd.setBrightness(0.6);
    joystick1.init();
    joystick2.init();
    button1.mode(PullUp);
}

void GameEngine::run() {
    init();
    while (true) {
        refreshDisplay();
        character.updatePosition(joystick1);
        if (button2 == 1) { // Assuming button2 is active low
            character.updateShootingDirection(joystick2, projectiles);
        }
        handleProjectiles();
        handleBossCollision();
        if (!boss.isDead()) {
            boss.update();
            boss.draw();
        }
        character.applyGravity();
        character.jump(button1 == 0);
        character.boundaryCheck();
        lcd.refresh();
        ThisThread::sleep_for(30ms);
    }
}

void GameEngine::handleProjectiles() {
    for (auto& p : projectiles) {
        p.update();
        lcd.setPixel(round(p.x), round(p.y), 1); // Example method, adjust to your LCD's API
    }
}

void GameEngine::handleBossCollision() {
    for (auto& p : projectiles) {
        if (p.x >= boss.x_pos && p.x <= boss.x_pos + 10 && p.y >= boss.y_pos && p.y <= boss.y_pos + 10) {
            boss.takeDamage();
            p.x = -10; // Move the projectile off-screen
            if (boss.hp <= 0) {
                boss.setDead(true);
            }
        }
    }
}

void GameEngine::refreshDisplay() {
    lcd.clear();
    lcd.drawRect(0, 0, 84, 48, FILL_TRANSPARENT);
    lcd.drawRect(character.x_pos, character.y_pos, 4, 7, FILL_BLACK);
    boss.draw();
}
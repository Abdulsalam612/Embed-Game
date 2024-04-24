#include "GameEngine.h"
#include "Bitmap.h"
#include "test.h"
#include "walk1_left.h"
#include "walk2_left.h"
#include "walk1_right.h"
#include "walk2_right.h"
#include "idle1.h"
#include "idle2.h"
#include "boss.h"
#include <string>


GameEngine::GameEngine(N5110& lcd, Joystick& joystick1, Joystick& joystick2, DigitalIn& button1, DigitalIn& button2)
    : lcd(lcd),  joystick1(joystick1), joystick2(joystick2), button1(button1), button2(button2),
      character(42, 24, 34,100), Enemy(&lcd, 42, 14, 8, 1), currentLevel(lcd) // Example initial positions, ground level, and Enemy parameters
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

bool GameEngine::run() {
    init();
    currentLevel.load();
    while (true) {
        currentLevel.update();
        refreshDisplay();
        character.updatePosition(joystick1);
        if (button2 == 1) {
            character.updateShootingDirection(joystick2, projectiles);
        }
        printEnemyHp();
        handleProjectiles();
        handleEnemyCollision();
        if (!Enemy.isDead()) {
            Enemy.update();
            Enemy.draw();
        } else {
            showVictoryScreen();
            return true;
        }
        character.applyGravity();
        character.jump(button1 == 0);
        character.boundaryCheck();
        lcd.refresh();
        ThisThread::sleep_for(30ms);

        currentLevel.update();
        if (character.isDead()) {
            lcd.clear();
            lcd.printString("Game Over", 0, 0);
            lcd.refresh();
            ThisThread::sleep_for(2s);
            return false;
        }
    }
    return false; // Add a default return statement
}

void GameEngine::showVictoryScreen() {
    lcd.clear();
    lcd.printString("Victory!", 0, 0);
    lcd.printString("Enemy Defeated", 0, 2);
    lcd.refresh();
    ThisThread::sleep_for(2s); // Display the victory screen for 2 seconds
}

void GameEngine::handleProjectiles() {
    for (auto& p : projectiles) {
        p.update();
        lcd.setPixel(round(p.x), round(p.y), 1); // Example method, adjust to your LCD's API
    }
}

void GameEngine::printEnemyHp() {
    printf("Enemy HP: %d\n", Enemy.getHp());
}

void GameEngine::handleEnemyCollision() {
    for (auto& p : projectiles) {
        if (p.x >= Enemy.x_pos && p.x <= Enemy.x_pos + boss_width && p.y >= Enemy.y_pos && p.y <= Enemy.y_pos + boss_height) {
            Enemy.takeDamage();
            p.x = -10; // Move the projectile off-screen
            if (Enemy.hp <= 0) {
                Enemy.setDead(true);
            }
        }
    }

    if (!character.isDead() && !Enemy.isDead()) {
        // Check for collision between character and Enemy sprite
        if (character.x_pos < Enemy.x_pos + boss_width &&
            character.x_pos + 17 > Enemy.x_pos &&
            character.y_pos < Enemy.y_pos + boss_height &&
            character.y_pos + 13 > Enemy.y_pos) {
            character.takeDamage(Enemy.damage);
        }
    }
}
    
void GameEngine::refreshDisplay() {
    lcd.clear();
    lcd.drawRect(0, 0, 84, 48, FILL_TRANSPARENT);
    
    lcd.printString("HP: ", 42, 0);
    lcd.printString(std::to_string(character.hp).c_str(), 64, 0);

    Direction dir = joystick1.get_direction();
    
    if (dir == E) {
        if (character.currentSprite == 0) {
            lcd.drawSprite(character.x_pos, character.y_pos, 17, 13, (int *)walk1_right);
        } else {
            lcd.drawSprite(character.x_pos, character.y_pos, 17, 13, (int *)walk2_right);
        }
    } else if (dir == W) {
        if (character.currentSprite == 0) {
            lcd.drawSprite(character.x_pos, character.y_pos, 17, 13, (int *)walk1_left);
        } else {
            lcd.drawSprite(character.x_pos, character.y_pos, 17, 13, (int *)walk2_left);
        }
    } else {
        if (character.idleFrame == 0) {
            lcd.drawSprite(character.x_pos, character.y_pos, 17, 11, (int *)idle1);
        } else {
            lcd.drawSprite(character.x_pos, character.y_pos, 17, 11, (int *)idle2);
        }
        
        // Update the idle frame every 10 game loops
        static int idleFrameCount = 0;
        idleFrameCount++;
        if (idleFrameCount >= 10) {
            character.idleFrame = !character.idleFrame;
            idleFrameCount = 0;
        }
    }
    
    Enemy.draw();
}
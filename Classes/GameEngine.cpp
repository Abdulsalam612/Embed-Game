#include "GameEngine.h"
#include "Bitmap.h"
#include "test.h"
#include "walk1_left.h"
#include "walk2_left.h"
#include "walk1_right.h"
#include "walk2_right.h"
#include "idle1.h"
#include "idle2.h"



GameEngine::GameEngine(N5110& lcd, Joystick& joystick1, Joystick& joystick2, DigitalIn& button1, DigitalIn& button2)
    : lcd(lcd),  joystick1(joystick1), joystick2(joystick2), button1(button1), button2(button2),
      character(42, 24, 34,1), boss(&lcd, 42, 5, 8, 1) // Example initial positions, ground level, and boss parameters
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
        if (button2 == 1) {
            character.updateShootingDirection(joystick2, projectiles);
        }
        printBossHp();
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

        if (character.isDead()) {
            lcd.clear();
            lcd.printString("Game Over", 0, 0);
            lcd.refresh();
            break;
        }
    }
}
void GameEngine::handleProjectiles() {
    for (auto& p : projectiles) {
        p.update();
        lcd.setPixel(round(p.x), round(p.y), 1); // Example method, adjust to your LCD's API
    }
}

void GameEngine::printBossHp() {
    printf("Boss HP: %d\n", boss.getHp());
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

    if (!character.isDead() && !boss.isDead() &&
        character.x_pos >= boss.x_pos && character.x_pos <= boss.x_pos + 10 &&
        character.y_pos >= boss.y_pos && character.y_pos <= boss.y_pos + 10) {
        character.takeDamage(boss.damage);
    }
}

void GameEngine::refreshDisplay() {
    lcd.clear();
    lcd.drawRect(0, 0, 84, 48, FILL_TRANSPARENT);
    
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
    
    boss.draw();
}
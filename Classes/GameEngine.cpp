#include "GameEngine.h"
#include "Bitmap.h"
#include "Enemy.h"
#include "walk.h"
#include "boss.h"
#include <string>


GameEngine::GameEngine(N5110& lcd, Joystick& joystick1, Joystick& joystick2, DigitalIn& button1, DigitalIn& button2)
    : lcd(lcd),  joystick1(joystick1), joystick2(joystick2), button1(button1), button2(button2),
      character(12, 24, 34,100), enemy(&lcd, 42, 14, 1, 1, 1.0f, 0.0f, 0.0f), currentLevel(lcd, button1) // Example initial positions, ground level, and Enemy parameters
{
}

void GameEngine::init() {
    lcd.init(LPH7366_1);
    lcd.setContrast(0.5);
    lcd.setBrightness(0.2);
    joystick1.init();
    joystick2.init();
    button1.mode(PullUp);
}

bool GameEngine::run() {
    init();

    // Spawn the character
    refreshDisplay();
    lcd.refresh();

    // Delay for 1 second after the character spawns
    ThisThread::sleep_for(1s);

    // Load the level (spawn the enemies)
    currentLevel.load(character.x_pos, character.y_pos);

    while (true) {
        currentLevel.update();
        refreshDisplay();
        character.updatePosition(joystick1);
        if (button2 == 1) {
            character.updateShootingDirection(joystick2, projectiles);
        }
        handleProjectiles();
        handleEnemyCollision();

        if (currentLevel.allEnemiesDefeated()) {
    if (currentLevel.getWave() == 1) {
        currentLevel.showSecondWaveDialogue();
        currentLevel.nextWave();

        ThisThread::sleep_for(1s);
        currentLevel.load(character.x_pos, character.y_pos);
    } else if (currentLevel.getWave() == 2) {
        currentLevel.showThirdWaveDialogue();
        currentLevel.nextWave();

        ThisThread::sleep_for(1s);
        currentLevel.load(character.x_pos, character.y_pos);
    } else if (currentLevel.getWave() == 3) {
        currentLevel.showFinalBossDialogue();
        currentLevel.nextWave(); // Ensure this method increments the wave count
        currentLevel.spawnFinalBoss(); // Ensure this spawns the final boss appropriately
    }
}

if (currentLevel.getWave() == 4) {
    currentLevel.updateFinalBoss();

    if (currentLevel.isFinalBossDefeated()) {
        showVictoryScreen();
        return true;
    }
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
            ThisThread::sleep_for(2s);
            return false;
        }
    }

    return false;
}


void GameEngine::showVictoryScreen() {
    lcd.clear();
    lcd.printString("Victory!", 0, 0);
    lcd.printString("Enemy Defeated", 0, 2);
    lcd.refresh();
    ThisThread::sleep_for(2s); // Display the victory screen for 2 seconds
}

void GameEngine::handleProjectiles() {
    for (auto it = projectiles.begin(); it != projectiles.end();) {
        it->update();
        
        // Remove the bullet if it goes out of bounds
        if (it->x < 4 || it->x >= 82 || it->y < 4 || it->y >= 46) {
            it = projectiles.erase(it);
        } else {
            // Draw a circle with a radius of 2 for each projectile
            lcd.drawCircle(round(it->x), round(it->y), 1, FILL_BLACK);
            ++it;
        }
    }
}

void GameEngine::printEnemyHp() {
    printf("Enemy HP: %d\n", enemy.getHp());
}

void GameEngine::handleEnemyCollision() {
    for (auto& p : projectiles) {
        for (auto& e : currentLevel.getEnemies()) {
            if (!e.isDead() && p.x >= e.x_pos && p.x <= e.x_pos + e.getWidth() && p.y >= e.y_pos && p.y <= e.y_pos + e.getHeight()) {
                const_cast<Enemy&>(e).takeDamage();
                p.x = -10; // Move the projectile off-screen
                if (e.hp <= 0) {
                    const_cast<Enemy&>(e).setDead(true);
                }
            }
        }
    }

    if (!character.isDead()) {
        for (auto& e : currentLevel.getEnemies()) {
            if (!e.isDead()) {
                // Adjust the hit box of the character
                int characterLeft = character.x_pos + 4;
                int characterRight = character.x_pos + 13;
                int characterTop = character.y_pos + 6;
                int characterBottom = character.y_pos + 10;

                // Check for collision between character's hit box and enemy sprite
                if (characterLeft < e.x_pos + e.getWidth() &&
                    characterRight > e.x_pos &&
                    characterTop < e.y_pos + e.getHeight() &&
                    characterBottom > e.y_pos) {
                    character.takeDamage(e.damage);
                }
            }
        }
    }
}
    
void GameEngine::refreshDisplay() {
    lcd.clear();
    lcd.drawRect(0, 0, 84, 48, FILL_TRANSPARENT);
    
    lcd.printString("HP: ", 5, 0);
    lcd.printString(std::to_string(character.hp).c_str(), 21, 0);

    Direction dir = joystick1.get_direction();

    for (auto& enemy : currentLevel.getEnemies()) {
        enemy.draw();
    }
    
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

}
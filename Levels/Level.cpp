// Level.cpp
#include "Level.h"
#include "FinalBoss.h"
#include "Dialogue.h"

Level::Level(N5110& lcd, DigitalIn& button)
    : lcd(lcd), button(button), boss(&lcd, 42, 0, 1, 2, 1.0f, 0.0f, 0.0f), wave(1),
      finalBoss(&lcd, 42, 0, 1, 2, 1.0f, 0.0f, 0.0f), finalBossSpawned(false) {}

void Level::load(float characterX, float characterY) {
    enemies.clear();
    // Spawn regular enemies at random positions
    int numEnemies;
    float enemySpeed;
    if (wave == 1) {
        numEnemies = 3;
        enemySpeed = 1.0f;
    } else if (wave == 2) {
        numEnemies = 5;
        enemySpeed = 1.0f;
    } else {
        numEnemies = 8;
        enemySpeed = 1.5f;
    }
    for (int i = 0; i < numEnemies; i++) {
        float x, y;
        bool validPosition = false;
        while (!validPosition) {
            if (wave == 1) {
                x = rand() % 74 + 5;  // Random x position between 5 and 78
                y = rand() % 38 + 5;  // Random y position between 5 and 42
            } else {
                x = rand() % 74 + 5;  // Random x position between 5 and 78
                y = rand() % 10 + 5;  // Random y position between 5 and 14 (top area)
            }
            // Check if the position is far enough from the character
            if (abs(x - characterX) > 20 || abs(y - characterY) > 20) {
                validPosition = true;
            }
        }
        enemies.emplace_back(&lcd, x, y, 1, 1, enemySpeed, 0.0f, 0.0f);
    }
}



void Level::showSecondWaveDialogue() {
    lcd.clear();
    lcd.printString("Get prepared", 0, 0);
    lcd.printString("for the", 0, 1);
    lcd.printString("second wave!", 0, 2);
    lcd.refresh();

    while (button == 1) {
        ThisThread::sleep_for(100ms);
    }
    while (button == 0) {
        ThisThread::sleep_for(100ms);
    }
}

void Level::showThirdWaveDialogue() {
    lcd.clear();
    lcd.printString("Brace yourself", 0, 0);
    lcd.printString("for the", 0, 1);
    lcd.printString("third wave!", 0, 2);
    lcd.printString("Enemies are", 0, 3);
    lcd.printString("faster now!", 0, 4);
    lcd.refresh();

    while (button == 1) {
        ThisThread::sleep_for(100ms);
    }
    while (button == 0) {
        ThisThread::sleep_for(100ms);
    }
}

int animspeed = 700;

void Level::showFinalBossDialogue() {
    lcd.clear();
    lcd.drawSprite(0, 0, 48, 84, (int *)sprite0);
    lcd.refresh();
    ThisThread::sleep_for((chrono::milliseconds(animspeed)));


    lcd.clear();
    lcd.drawSprite(0, 0, 48, 84, (int *)sprite1);
    lcd.refresh();
    ThisThread::sleep_for((chrono::milliseconds(animspeed)));

    lcd.clear();
    lcd.drawSprite(0, 0, 48, 84, (int *)sprite2);
    lcd.refresh();
    ThisThread::sleep_for((chrono::milliseconds(animspeed)));

    lcd.clear();
    lcd.drawSprite(0, 0, 48, 84, (int *)sprite3);
    lcd.refresh();
    ThisThread::sleep_for((chrono::milliseconds(animspeed)));

    lcd.clear();
    lcd.drawSprite(0, 0, 48, 84, (int *)sprite4);
    lcd.refresh();
    ThisThread::sleep_for(2s);

    lcd.clear();
    lcd.drawSprite(0, 0, 48, 84, (int *)sprite5);
    lcd.refresh();
    ThisThread::sleep_for(2s);

    lcd.clear();
    lcd.drawSprite(0, 0, 48, 84, (int *)sprite6);
    lcd.refresh();
    ThisThread::sleep_for(2s);

    lcd.clear();
    lcd.drawSprite(0, 0, 48, 84, (int *)sprite7);
    lcd.refresh();
    ThisThread::sleep_for(700ms);

    lcd.clear();
    lcd.drawSprite(0, 0, 48, 84, (int *)sprite8);
    lcd.refresh();
    ThisThread::sleep_for(700ms);

    lcd.clear();
    lcd.drawSprite(0, 0, 48, 84, (int *)sprite9);
    lcd.refresh();
    ThisThread::sleep_for(700ms);

    lcd.clear();
    lcd.drawSprite(0, 0, 48, 84, (int *)sprite10);
    lcd.refresh();
    ThisThread::sleep_for(700ms);

      lcd.refresh();

    // Wait for the button to be released
    while (button == 0) {
        ThisThread::sleep_for(100ms);
    }

    // Wait for the button to be pressed
    while (button == 1) {
        ThisThread::sleep_for(100ms);
    }

    // Wait for the button to be released again
    while (button == 0) {
        ThisThread::sleep_for(100ms);
    }

}

void Level::spawnFinalBoss() {
    finalBoss = Enemy(&lcd, 42, 0, 20, 2, 1.0f, 0.0f, 0.0f);
    finalBossSpawned = true;
}

void Level::setCharacterPosition(float x, float y) {
    characterX = x;
    characterY = y;
}

void Level::updateFinalBoss() {
    if (finalBossSpawned && !finalBoss.isDead()) {
        // Update final boss movement using sine wave pattern
        static float t = 0.0f;
        t += 0.05f;
        finalBoss.x_pos = 42 + 20 * sin(t);
        finalBoss.y_pos = 24 + 20 * cos(t * 0.7f);

        // Shoot bullets from the final boss towards the character
        static int bulletTimer = 0;
        bulletTimer++;
        if (bulletTimer >= 50) {
            // Calculate the direction vector from the final boss to the character
            float dx = characterX - finalBoss.x_pos;
            float dy = characterY - finalBoss.y_pos;
            float magnitude = sqrt(dx * dx + dy * dy);
            dx /= magnitude;
            dy /= magnitude;

            // Shoot bullets from the left side of the boss
            enemies.emplace_back(&lcd, finalBoss.x_pos - 5, finalBoss.y_pos + 5, 1, 1, 2.0f, dx, dy);
            // Shoot bullets from the right side of the boss
            enemies.emplace_back(&lcd, finalBoss.x_pos + 24, finalBoss.y_pos + 5, 1, 1, 2.0f, dx, dy);
            bulletTimer = 0;
        }

        lcd.drawSprite(finalBoss.x_pos, finalBoss.y_pos, FinalBoss_width, FinalBoss_height, (int *)FinalBoss);
    }
}

bool Level::isFinalBossDefeated() const {
    return finalBossSpawned && finalBoss.isDead();
}

void Level::nextWave() {
    wave++;
}

int Level::getWave() const {
    return wave;
}

void Level::update() {
    for (auto& enemy : enemies) {
        if (!enemy.isDead()) {
            enemy.update();
            enemy.draw();
        }
    }

    if (!boss.isDead()) {
        boss.update();
        boss.draw();
    }
}

bool Level::allEnemiesDefeated() {
    for (const auto& enemy : enemies) {
        if (!enemy.isDead()) {
            return false;
        }
    }
    return true;
}

void Level::showBossDialogue() {
    lcd.clear();
    lcd.printString("Boss:", 0, 0);
    lcd.printString("You dare ", 0, 1);
    lcd.printString("to challenge ", 0, 2);
    lcd.printString("me little ", 0, 3);
    lcd.printString("teacup??", 0, 4);
    lcd.refresh();

    while (button == 1) {
        ThisThread::sleep_for(100ms);
    }
    while (button == 0) {
        ThisThread::sleep_for(100ms);
    }

    lcd.clear();
    lcd.printString("Boss:", 0, 0);
    lcd.printString("Prepare to be ", 0, 2);
    lcd.printString("shattered!", 0, 3);
    lcd.refresh();

    while (button == 1) {
        ThisThread::sleep_for(100ms);
    }
    while (button == 0) {
        ThisThread::sleep_for(100ms);
    }

    lcd.clear();
    lcd.printString("Teacup:", 0, 0);
    lcd.printString("I won't let ", 0, 1);
    lcd.printString("you terrorize", 0, 2);
    lcd.printString("this land ", 0, 3);
    lcd.printString("any longer!", 0, 4);
    lcd.refresh();

    while (button == 1) {
        ThisThread::sleep_for(100ms);
    }
    while (button == 0) {
        ThisThread::sleep_for(100ms);
    }

    lcd.clear();
    lcd.printString("Teacup:", 8, 0);
    lcd.printString("   Lets ", 8, 2);
    lcd.printString("   Settle", 8, 3);
    lcd.printString("   This", 8, 4);
    lcd.refresh();

    while (button == 1) {
        ThisThread::sleep_for(100ms);
    }
    while (button == 0) {
        ThisThread::sleep_for(100ms);
    }

    lcd.clear();
    lcd.printString("Boss:", 0, 0);
    lcd.printString("   Have fun", 0, 1);
    lcd.printString("   With my  ", 0, 2);
    lcd.printString("   .... ", 0, 3);
    lcd.printString("   Minions (; ", 0, 4);
    lcd.refresh();

    while (button == 1) {
        ThisThread::sleep_for(100ms);
    }
    while (button == 0) {
        ThisThread::sleep_for(100ms);
    }

}
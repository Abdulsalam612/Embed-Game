// Level.cpp
#include "Level.h"

Level::Level(N5110& lcd, DigitalIn& button)
    : lcd(lcd), button(button), boss(&lcd, 42, 0, 20, 2,1.0f), wave(1) {}

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
        enemies.emplace_back(&lcd, x, y, 4, 1, enemySpeed);
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
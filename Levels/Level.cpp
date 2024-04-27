// Level.cpp
#include "Level.h"

Level::Level(N5110& lcd, DigitalIn& button)
    : lcd(lcd), button(button), boss(&lcd, 42, 0, 20, 2) {}

void Level::load() {
    enemies.clear();
    // Spawn regular enemies
    enemies.emplace_back(&lcd, 10, 24, 5, 1);
    enemies.emplace_back(&lcd, 30, 24, 5, 1);
    enemies.emplace_back(&lcd, 50, 24, 5, 1);
    enemies.emplace_back(&lcd, 70, 24, 5, 1);
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
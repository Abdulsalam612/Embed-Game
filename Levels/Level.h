// Level.h
#ifndef LEVEL_H
#define LEVEL_H

#include "mbed.h"
#include "N5110.h"
#include "Enemy.h"
#include <vector>

class Level {
public:
    Level(N5110& lcd, DigitalIn& button);
    void load(float characterX, float characterY);
    void showThirdWaveDialogue();
    void update();
    void showBossDialogue();
    bool allEnemiesDefeated();
    void showSecondWaveDialogue();
    void nextWave();
    int getWave() const;
    const std::vector<Enemy>& getEnemies() const { return enemies; }
    void showFinalBossDialogue();
    void spawnFinalBoss();
    void updateFinalBoss();
    bool isFinalBossDefeated() const;
    void setCharacterPosition(float x, float y);
    Enemy& getFinalBoss() { return finalBoss; }

private:
    N5110& lcd;
    DigitalIn& button;
    std::vector<Enemy> enemies;
    Enemy boss;
    int wave;
    Enemy finalBoss;
    bool finalBossSpawned;
    float characterX;
    float characterY;
};

#endif
#pragma once
#include <vector>

class Player;
class Enemy;
class Bullet;
class Explosion;

class Game {
    Player*            player_;
    std::vector<Enemy> enemies_;
    std::vector<Bullet> bullets_;
    std::vector<Explosion> explosions_;
    int score_, wave_;
    bool over_, win_;
public:
    Game();
    ~Game();
    void run();
private:
    void initWave();
    void handleInput();
    void updateAll();
    void drawAll();
    void detectCollisions();
    void drawUI();
};
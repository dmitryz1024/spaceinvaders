#pragma once
#include "Entity.h"
#include <vector>
class Bullet;

class Player : public Entity {
    int lives_, cd_, cdMax_;
    std::vector<Bullet>& bullets_;
public:
    Player(int x, int y, std::vector<Bullet>& bullets);
    void update() override;
    void draw() const override;
    void moveLeft();
    void moveRight(int maxX);
    bool canShoot() const;
    void shoot();
    bool isDead() const { return lives_<=0; }
    void loseLife() { if (lives_>0) --lives_; }
};
#pragma once
#include "Entity.h"
#include <vector>
class Bullet;

class Enemy : public Entity {
    int dir_, left_, right_, cd_, cdMax_;
    int moveTick_, moveChangeTick_, moveDelay_;
    std::vector<Bullet>& bullets_;
public:
    Enemy(int x, int y, std::vector<Bullet>& bullets, int left, int right);
    void update() override;
    void draw() const override { Entity::draw(); }
};
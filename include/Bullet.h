#pragma once
#include "Entity.h"

class Bullet : public Entity {
    int dy_;
public:
    Bullet(int x, int y, int dy);
    void update() override;
    void draw()  const override { Entity::draw(); }
    int getDy() const { return dy_; }
};
#pragma once
#include "Entity.h"

class Explosion : public Entity {
    int timer_;
    int frame_;
public:
    Explosion(int x, int y);
    void update() override;
    void draw() const override;
};
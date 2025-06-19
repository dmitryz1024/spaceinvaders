#include "Bullet.h"

Bullet::Bullet(int x, int y, int dy)
  : Entity(x,y,'|'), dy_(dy)
{}

void Bullet::update() {
    y_ += dy_;
    if (y_<0 || y_>=LINES) alive_ = false;
}
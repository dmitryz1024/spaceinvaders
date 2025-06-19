#include "Enemy.h"
#include "Bullet.h"
#include <cstdlib>

Enemy::Enemy(int x, int y, std::vector<Bullet>& bullets, int left, int right)
  : Entity(x,y,'M'),
    dir_(1), left_(left), right_(right),
    bullets_(bullets),
    cd_(rand()%10), cdMax_(40),
    moveTick_(0), moveChangeTick_(rand()%20 + 10),
    moveDelay_(2)
{}

void Enemy::update() {
    if (isAlive()) {
        moveTick_++;
        if (moveTick_ >= moveDelay_) {
            moveTick_ = 0;

            if (--moveChangeTick_ <= 0) {
                if (rand() % 2 == 0) dir_ = -dir_;
                moveChangeTick_ = rand()%20 + 10;
            }

            x_ += dir_;
            if (x_ <= left_)  { x_ = left_;  dir_ = 1;  y_++; }
            if (x_ >= right_) { x_ = right_; dir_ = -1; y_++; }
        }
    }

    if (isAlive()) {
        if (cd_ > 0) --cd_;
        else {
            bullets_.emplace_back(x_, y_+1, +1);
            cd_ = cdMax_;
        }
    }
}
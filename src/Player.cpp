#include "Player.h"
#include "Bullet.h"
#include <curses.h>

Player::Player(int x, int y, std::vector<Bullet>& bullets)
  : Entity(x,y,'^'), lives_(3), cd_(0), cdMax_(4), bullets_(bullets)
{}

void Player::update() {
    if (cd_>0) --cd_;
}

void Player::draw() const {
    mvprintw(LINES-1, 2, "Lives: %d", lives_);
    mvaddch(y_, x_, sym_);
}

void Player::moveLeft()  { if (x_>1) --x_; }
void Player::moveRight(int maxX) { if (x_<maxX-2) ++x_; }
bool Player::canShoot() const { return cd_==0; }
void Player::shoot() {
    if (!canShoot()) return;
    bullets_.emplace_back(x_, y_-1, -1);
    cd_ = cdMax_;
}
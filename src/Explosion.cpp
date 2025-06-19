#include "Explosion.h"
#include <curses.h>

Explosion::Explosion(int x, int y)
  : Entity(x,y,'*'), timer_(15), frame_(0)
{}

void Explosion::update() {
    ++frame_;
    if (--timer_ <= 0) alive_ = false;
}

void Explosion::draw() const {
    if (!alive_) return;
    chtype ch;
    int color = 0;
    if (frame_ < 5)      { ch = 'o'; color = 1; }
    else if (frame_ < 10){ ch = '*'; color = 2; }
    else                 { ch = '+'; color = 3; }

    attr_t old = A_NORMAL;
#ifdef A_BOLD
    if (frame_ < 5) old = A_BOLD;
#endif

    attron(COLOR_PAIR(color) | old);
    mvaddch(y_, x_, ch);
    attroff(COLOR_PAIR(color) | old);
}
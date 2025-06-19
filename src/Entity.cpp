#include "Entity.h"

Entity::Entity(int x, int y, char sym)
  : x_(x), y_(y), sym_(sym), alive_(true) {}

void Entity::draw() const {
    if (!alive_) return;
    mvaddch(y_, x_, sym_);
}
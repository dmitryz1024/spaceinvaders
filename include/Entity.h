#pragma once
#include <curses.h>

class Entity {
protected:
    int x_, y_; char sym_; bool alive_;
public:
    Entity(int x, int y, char sym);
    virtual ~Entity() = default;
    virtual void update() = 0;
    virtual void draw() const;
    bool isAlive() const { return alive_; }
    int getX() const { return x_; }
    int getY() const { return y_; }
    void kill() { alive_ = false; }
};
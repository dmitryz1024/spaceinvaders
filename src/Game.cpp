#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Explosion.h"
#include <curses.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cstring>

Game::Game()
  : player_(nullptr), score_(0), wave_(0), over_(false), win_(false)
{
    std::srand(std::time(nullptr));
    initscr();
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    curs_set(0);
    cbreak();
    noecho();
    curs_set(0);
    leaveok(stdscr, TRUE);
    keypad(stdscr, TRUE);
    timeout(0);
    initWave();
}

Game::~Game() {
    delete player_;
    endwin();
}

void Game::initWave() {
    ++wave_;
    bullets_.clear();
    explosions_.clear();
    enemies_.clear();

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    delete player_;
    player_ = new Player(maxX / 2, maxY - 2, bullets_);

    int rows = 1 + wave_ / 2;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < 10; ++j) {
            int left = 1;
            int right = maxX - 2;
            enemies_.emplace_back(3 + j * 6, 2 + i * 2, bullets_, left, right);
        }
    }
}

void Game::handleInput() {
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    int ch = getch();

    switch (ch) {
        case KEY_LEFT:
        case 'a':
            player_->moveLeft();
            break;
        case KEY_RIGHT:
        case 'd':
            player_->moveRight(maxX);
            break;
        case ' ':
            if (player_->canShoot()) player_->shoot();
            break;
        case 'q':
            over_ = true;
            break;
        default:
            break;
    }
}

void Game::updateAll() {
    player_->update();
    for (auto& e : enemies_)    e.update();
    for (auto& b : bullets_)    b.update();
    for (auto& ex: explosions_) ex.update();
}

void Game::drawAll() {
    erase();
    for (auto& e : enemies_)    if (e.isAlive()) e.draw();
    for (auto& b : bullets_)    if (b.isAlive()) b.draw();
    for (auto& ex: explosions_) if (ex.isAlive()) ex.draw();
    player_->draw();
    drawUI();
    refresh();
}

void Game::detectCollisions() {
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    for (auto& e : enemies_) {
        if (e.isAlive() && e.getY() >= maxY - 2) {
            over_ = true;
            return;
        }
    }

    for (auto& b : bullets_) {
        if (!b.isAlive() || b.getDy() >= 0) continue;
        for (auto& e : enemies_) {
            if (e.isAlive() && b.getX() == e.getX() && b.getY() == e.getY()) {
                e.kill();
                b.kill();
                explosions_.emplace_back(e.getX(), e.getY());
                score_ += 10;
            }
        }
    }

    for (auto& b : bullets_) {
        if (!b.isAlive() || b.getDy() <= 0) continue; // dy > 0 — пули врагов
        if (b.getX() == player_->getX() && b.getY() == player_->getY()) {
            b.kill();
            player_->loseLife();
            explosions_.emplace_back(player_->getX(), player_->getY());
            if (player_->isDead()) over_ = true;
        }
    }

    bool any = false;
    for (auto& e : enemies_)
        if (e.isAlive()) any = true;
    if (!any) {
        if (wave_ >= 5) win_ = true;
        else initWave();
    }

    bullets_.erase(std::remove_if(
        bullets_.begin(), bullets_.end(),
        [](auto& b){ return !b.isAlive(); }
    ), bullets_.end());
    explosions_.erase(std::remove_if(
        explosions_.begin(), explosions_.end(),
        [](auto& ex){ return !ex.isAlive(); }
    ), explosions_.end());
}

void Game::drawUI() {
    mvprintw(0, 2, "Score: %d  Wave: %d", score_, wave_);
}

void Game::run() {
    while (true) {
        over_ = false;
        win_ = false;
        wave_ = 0;
        score_ = 0;
        initWave();
        timeout(0);
        while (!over_ && !win_) {
            handleInput();
            updateAll();
            detectCollisions();
            drawAll();
            napms(30);
        }

        erase();
        const char* msg = win_ ? "YOU WIN!" : "GAME OVER";
        int maxY, maxX; getmaxyx(stdscr, maxY, maxX);
        mvprintw(maxY/2, (maxX - std::strlen(msg))/2, "%s", msg);
        mvprintw(maxY/2+1, (maxX-21)/2, "q - exit, r - restart");
        nodelay(stdscr, FALSE);
        refresh();
        int ch;
        do {
            ch = getch();
        } while (ch != 'q' && ch != 'r');
        if (ch == 'q') break;
        timeout(0);
    }
}
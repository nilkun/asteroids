#include "Asteroids.h"
#include <iostream>

Asteroids::Asteroids() {
    // vecAsteroids.push_back({10.0f, 10.0f, 8.0f, -6.0f, (int)16, 0.0f});
}

bool Asteroids::update(float fElapsedTime, SDL_Rect &temp) {
    for (auto &a : vecAsteroids) {
        a.x += a.dx * fElapsedTime;
        a.y += a.dy * fElapsedTime;

        temp.x = a.x;
        temp.y = a.y;
    }
    return true;
};

Ship::Ship() {
     position = { 0.0f, 0.0f };
     direction = { 0.0f, 0.0f };
     angle = 0;
     size = 15;
}
bool Ship::collision(Ship *ship) {
    // float realSize = size * 6.28318f;
    float distanceX = ship -> position.first - position.first;
    float distanceY = ship -> position.second - position.second;
    float hypoteneuse = distanceX * distanceX + distanceY * distanceY;
    float radius = size * size * size * size;;
    // std::cout << hypoteneuse << " < " << radius << std::endl;

    if(hypoteneuse < radius) return true;
    return false;
  }
void Ship::update(float fElapsedTime, const int SCREENWIDTH, const int SCREENHEIGHT) {
    position.first += direction.first * fElapsedTime;
    position.second += direction.second * fElapsedTime;

    if(position.first < 0) position.first += SCREENWIDTH;
    else if(position.first >= SCREENWIDTH) position.first -=SCREENWIDTH;

    if(position.second < 0) position.second += SCREENHEIGHT;
    else if(position.second >= SCREENHEIGHT) position.second -=SCREENHEIGHT;
}
bool Ship::updateB(float fElapsedTime, const int SCREENWIDTH, const int SCREENHEIGHT) {
    position.first += direction.first * fElapsedTime;
    position.second += direction.second * fElapsedTime;

    if((position.first < 0) || (position.first >= SCREENWIDTH) ||(position.second < 0)
        ||(position.second >= SCREENHEIGHT)) return true;
    return false;
}
void Ship::fire() {
    Ship ship;
    bullets.push_back(ship);
    bullets.back().position.first = position.first;
    bullets.back().position.second = position.second;
    bullets.back().direction.first = 400 * sin(angle);
    bullets.back().direction.second = 400 * -cos(angle);
}

Ship Ship::copy() {
    Ship ship;
    ship.direction = direction;
    ship.position = position;

    return ship;
}

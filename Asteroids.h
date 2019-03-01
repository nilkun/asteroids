#ifndef ASTEROIDS
#define ASTEROIDS

#include <vector>
#include <SDL2/SDL.h>

struct sSpaceObject {
        float x;
        float y;
        float dx;
        float dy;
        int nSize;
        float angle;
};  
struct sPlayer : sSpaceObject {
    float mx[3] = { 6 * 0.0f, 6 *-2.5f, 6 *2.5f };
    float my[3] = { 6 * -5.5f, 6 *2.5f, 6 *2.5f };
    float sx[3];
    float sy[3];
};

class Asteroids {
public:
    Asteroids();
    
    std::vector<sSpaceObject>  vecAsteroids;

    bool update(float fElapsedTime, SDL_Rect &temp);
};

class Model2D {
  public:
  std::vector<std::pair<float, float>> model;
  Model2D() {
  }
};


class Ship : public Model2D {
  public:
    std::pair<float, float> position;
    std::pair<float, float> direction;
    float angle;
    float size;
    std::vector<Ship> bullets;
  Ship();
  void update(float fElapsedTime, const int SCREENWIDTH, const int SCREENHEIGHT);

  bool updateB(float fElapsedTime, const int SCREENWIDTH, const int SCREENHEIGHT);
  void fire();
  bool collision(Ship *ship);
  Ship copy();
 
};

class Ships {
public:
    std::vector<Ship> arr;
    Ships(){};
};
#endif
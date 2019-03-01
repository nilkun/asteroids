#include <SDL2/SDL.h>
#include "Asteroids.h"
#include "../engine/src/headers/ScreenManager.h"
#include "EventHandler.h"
#include <iostream>
#include <vector>
#include <cstdio>


const int SCREENWIDTH = 960;
const int SCREENHEIGHT = 600;
bool bLeftEdge = false;
bool bRightEdge = false;
bool bTopEdge = false;
bool bBottomEdge = false;

void renderLine(std::pair<float, float> point1, 
  std::pair<float, float> point2, 
  SDL_Renderer *renderer,
  float x, float y) 
{
  SDL_RenderDrawLine(renderer, point1.first + x, point1.second + y, point2.first + x, point2.second + y);
}



void drawWireFrame(Ship *ship, SDL_Renderer *renderer, float fElapsedTime) {

  const int BOTTOM = 0;
  const int TOP = 1;
  const int LEFT = 2;
  const int RIGHT = 3;

  // current heading of the ship
  std::vector<std::pair<float, float>> localPosition(ship -> model.size());

  // get indices to draw extra
  std::vector<std::pair<int, int>> idx;

  // set first before loop
  localPosition[0].first = ship -> size *  (ship -> model[0].first * cosf(ship -> angle) - ship -> model[0].second * sinf(ship -> angle));
  localPosition[0].second = ship -> size * (ship -> model[0].first * sinf(ship -> angle) + ship -> model[0].second * cosf(ship -> angle));
        
  for(int i = 1; i < ship -> model.size(); i++) {
    localPosition[i].first = ship -> size * (ship -> model[i].first * cosf(ship -> angle)  - ship -> model[i].second * sinf(ship -> angle));
    localPosition[i].second = ship -> size * (ship -> model[i].first * sinf(ship -> angle) + ship -> model[i].second * cosf(ship -> angle));
    SDL_RenderDrawLine(renderer, 
                        ship -> position.first + localPosition[i-1].first, 
                        ship -> position.second + localPosition[i-1].second, 
                        ship -> position.first + localPosition[i].first,
                        ship -> position.second + localPosition[i].second);

    // Wrap around
    if((ship -> position.first + localPosition[i].first) >= SCREENWIDTH) {
      idx.push_back(std::make_pair(i, LEFT));
    }
    else if((ship -> position.first + localPosition[i].first) < 0) {
      idx.push_back(std::make_pair(i, RIGHT));
    }
    if((ship -> position.second + localPosition[i].second) >= SCREENHEIGHT) {
      idx.push_back(std::make_pair(i, TOP));
    }
    else if((ship -> position.second + localPosition[i].second) < 0) {
      idx.push_back(std::make_pair(i, BOTTOM));
    }
  }

  // Final line
  SDL_RenderDrawLine(renderer, 
                    ship -> position.first + localPosition[0].first, 
                    ship -> position.second + localPosition[0].second, 
                    ship -> position.first + localPosition.back().first,
                    ship -> position.second + localPosition.back().second);

  if((ship -> position.first + localPosition[0].first) >= SCREENWIDTH) {
    idx.push_back(std::make_pair(0, LEFT));
  }
  else if((ship -> position.first + localPosition[0].first) < 0) {
    idx.push_back(std::make_pair(0, RIGHT));
  }
  if((ship -> position.second + localPosition[0].second) >= SCREENHEIGHT) {
    idx.push_back(std::make_pair(0, TOP));
  }
  else if((ship -> position.second + localPosition[0].second) < 0) {
    idx.push_back(std::make_pair(0, BOTTOM));
  }
  
  for(int i = 0; i < idx.size(); i++) {
    int x = 0;
    int y = 0;
    switch(idx[i].second) {
      case TOP:
      {
        y = -SCREENHEIGHT;
        break;
        }
      case BOTTOM:
      {
        y = SCREENHEIGHT;
        break;}
      case LEFT:
      {
        x = -SCREENWIDTH;
        break;
      }
      case RIGHT:
      {
        x = SCREENWIDTH;
        break;
      }
    }
    if(idx[i].first > 0) {
    renderLine(localPosition[idx[i].first], 
      localPosition[idx[i].first-1], 
      renderer, 
      ship -> position.first + x,
      ship -> position.second + y);
    }
    else {
    renderLine(localPosition[idx[i].first], 
      localPosition.back(), 
      renderer, 
      ship -> position.first + x,
      ship -> position.second + y);
    }
    if(idx[i].first < (ship -> model.size()-1)) {
      renderLine(localPosition[idx[i].first], 
        localPosition[idx[i].first+1], 
        renderer, 
        ship -> position.first + x,
        ship -> position.second + y);
    }
    else  {
      renderLine(localPosition[idx[i].first], 
        localPosition[0], 
        renderer, 
        ship -> position.first + x,
        ship -> position.second + y);}
  }
  
  
  // if((ship -> position.first + localPosition[0].first) >= SCREENWIDTH) {
  //   renderLine(localPosition[0], localPosition[1], renderer, ship -> position.first - SCREENWIDTH,ship -> position.second);
  //   renderLine(localPosition[0], localPosition.back(), renderer, ship -> position.first - SCREENWIDTH,ship -> position.second);
  // }
  // else if((ship -> position.first + localPosition[0].first) < 0) {
  //   renderLine(localPosition[0], localPosition[1], renderer, ship -> position.first + SCREENWIDTH,ship -> position.second);
  //   renderLine(localPosition[0], localPosition.back(), renderer, ship -> position.first + SCREENWIDTH,ship -> position.second);
  // }
  // if((ship -> position.second + localPosition[0].second) >= SCREENHEIGHT) {
  //   renderLine(localPosition[0], localPosition[1], renderer, ship -> position.first, ship -> position.second - SCREENHEIGHT);
  //   renderLine(localPosition[0], localPosition.back(), renderer, ship -> position.first, ship -> position.second - SCREENHEIGHT);
  // }
  // else if((ship -> position.second + localPosition[0].second) < 0) {
  //   renderLine(localPosition[0], localPosition[1], renderer, ship -> position.first, ship -> position.second + SCREENHEIGHT);
  //   renderLine(localPosition[0], localPosition.back(), renderer, ship -> position.first, ship -> position.second + SCREENHEIGHT);
  // }

};      

      
//       void updatePlayer(sPlayer &player, float fElapsedTime) {
      
//           player.x += player.dx * fElapsedTime;
//     player.y += player.dy * fElapsedTime;
    
//     if(player.x < 0) player.x = SCREENWIDTH + player.x;
//     if(player.y < 0) player.y = SCREENHEIGHT + player.y;
//     if(player.x >= SCREENWIDTH) player.x =  player.x - SCREENWIDTH;
//     if(player.y >= SCREENHEIGHT) player.y = player.y - SCREENHEIGHT;
    
//     for(int i = 0; i < 3; i++) {
//       // 
//         player.sx[i] = player.mx[i] * cosf(player.angle) - player.my[i] * sinf(player.angle);
//         player.sy[i] = player.mx[i] * sinf(player.angle) + player.my[i] * cosf(player.angle);
//       if(player.sx[i] >= SCREENWIDTH) bLeftEdge = true;
//       else if(player.sx[i] < 0) bRightEdge = true;
//       if(player.sy[i] >= SCREENHEIGHT) bTopEdge = true;
//       else if(player.sy[i] < 0) bBottomEdge = true;
//     }
void init(Ship** ship, Ships** asteroids) {


    *ship = new Ship;
    *asteroids = new Ships;

    Ship aste;
    (*asteroids) -> arr.push_back(aste);  

    (*ship) -> position = { SCREENWIDTH / 2.0f, SCREENHEIGHT / 2.0f };
    (*ship) -> model = { { 0.0f,   -5.0f },
                      { -2.5f,  2.5f  },
                      { 2.5f,   2.5f  } };
    (*ship) -> size = 5;

    int idx=0;

    //ASTEROID CREATION
    (*asteroids) -> arr[idx].size = 12;
    (*asteroids)->arr[idx].angle = 1;
    (*asteroids)->arr[idx].position = std::make_pair(120.0f, 120.0f);
    (*asteroids)->arr[idx].direction = std::make_pair(48.0f, -36.0f);

    int verts = 40;
    for(int i= 0; i < verts; i++) {
      float radius = (*asteroids) -> arr[idx].size;
      float a = ((float)i / (float)verts) * 6.28318f; // get 20 angles points
      float scale = 1 - ((rand()%10) *.01);
      std::cout << scale << std::endl;
      (*asteroids) -> arr[idx].model.push_back(std::make_pair(scale * radius * sinf(a),scale * radius * cosf(a)));
    }
};

void restart(Ship** ship, Ships** asteroids) {
  delete (*ship);
  delete (*asteroids); 
  init(ship, asteroids);
};

int main()
{

  srand(SDL_GetTicks());

  Ship *ship;
  Ships *asteroids; 

  EventHandler events;

  init(&ship, &asteroids);
  Screen *screen = Screen::instance();
  screen -> init("Asteroids", 960, 600);

  SDL_Renderer *renderer = screen -> getRenderer();

  // not necessary to reinitialize
  float fElapsedTime = 0;
  float previousTime = SDL_GetTicks();
  float currentTime = SDL_GetTicks();
  
  while(true) {
    previousTime = currentTime;
    currentTime = SDL_GetTicks();
    fElapsedTime = (currentTime - previousTime) * 0.001;
    screen -> clear();
     
// TODO collision bullet and asteroid create new asteroid;
    for(int idx = asteroids -> arr.size()-1; idx >= 0; idx--) {

      asteroids -> arr[idx].update(fElapsedTime, SCREENWIDTH, SCREENHEIGHT);
      if(asteroids -> arr[idx].collision(ship)) restart(&ship, &asteroids);
      for(int i = 0; i < ship -> bullets.size(); i++) {
        if(asteroids -> arr[idx].collision(&(ship -> bullets[i]))) {
          ship -> bullets.erase(ship -> bullets.begin() + i);
           
          if(asteroids -> arr[idx].size > 4) {

          
          float no1 = (float)rand() / (float)RAND_MAX * 6.28318f; 
          float no2 = (float)rand() / (float)RAND_MAX * 6.28318f;
          float no3 = (float)rand() / (float)RAND_MAX * 6.28318f; 
          float no4 = (float)rand() / (float)RAND_MAX * 6.28318f;
          Ship one;
          one.size = asteroids -> arr[idx].size / 2;
          one.angle = 1;
          one.position = std::make_pair(asteroids -> arr[idx].position.first, asteroids -> arr[idx].position.second);
          one.direction = std::make_pair( no1, no2);

          int verts = asteroids -> arr[idx].model.size();
          for(int i= 0; i < verts; i++) {
            float radius = one.size;
            float a = ((float)i / (float)verts) * 6.28318f; // get 20 angles points
            float scale = 1 - ((rand()%10) *.01);
            std::cout << scale << std::endl;
            one.model.push_back(std::make_pair(scale * radius * sinf(a), scale * radius * cosf(a)));
          }

          Ship two;
          two.size = asteroids -> arr[idx].size / 2;
          two.angle = 1;
          two.position = std::make_pair(asteroids -> arr[idx].position.first, asteroids -> arr[idx].position.second);
          two.direction = std::make_pair(no3, no4);

          verts = asteroids -> arr[idx].model.size();
          for(int i= 0; i < verts; i++) {
            float radius = two.size;
            float a = ((float)i / (float)verts) * 6.28318f; // get 20 angles points
            float scale = 1 - ((rand()%10) *.01);
            std::cout << scale << std::endl;
            two.model.push_back(std::make_pair(scale * radius * sinf(a), scale * radius * cosf(a)));

          }
            asteroids -> arr.push_back(one);
            asteroids -> arr.push_back(two);
          };
          asteroids -> arr.erase(asteroids -> arr.begin() + idx);
          
        };
      };
    };

    ship -> update(fElapsedTime, SCREENWIDTH, SCREENHEIGHT);
    events.poll(ship, fElapsedTime);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    
    int idx = 0;        
    std::vector<int> removeBullet;

    for(auto &b : ship -> bullets) {
      if(b.updateB(fElapsedTime, SCREENWIDTH, SCREENHEIGHT)) removeBullet.push_back(idx);
      SDL_RenderDrawPoint(renderer, b.position.first, b.position.second);
      idx++;
    }

    while(!removeBullet.empty()) {
      ship -> bullets.erase(ship -> bullets.begin() + removeBullet.back());
      removeBullet.pop_back();
    }

    drawWireFrame(ship, renderer, fElapsedTime);

    for(auto &aste: asteroids -> arr) {
      drawWireFrame(&aste, renderer, fElapsedTime);
    }

    screen -> render();
  };
  return 0;
}
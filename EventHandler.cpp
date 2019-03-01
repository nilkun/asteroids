#include "EventHandler.h"
#include <iostream>

EventHandler::EventHandler() {  };
void EventHandler::poll(Ship *ship, float fElapsedTime)
{
  
  while(SDL_PollEvent(&event)) 
  {
    switch (event.type) 
    {
      case SDL_QUIT: 
      {
        exit(1);
        break;
      }
      case SDL_KEYDOWN:
        switch(event.key.keysym.sym)
        {
          case SDLK_UP:
          {
            ship -> direction.first += sin(ship -> angle) * (120.0f * fElapsedTime);
            ship -> direction.second += -cos(ship -> angle) * (120.0f * fElapsedTime);
            break;
          }
          case SDLK_LEFT:
          {
            ship -> angle -=5.0f * fElapsedTime;   
            // std::cout << "Turning left" << std::endl;     
            break;
          }
          case SDLK_RIGHT:
          {
            ship -> angle +=5.0f * fElapsedTime;
            break;
          }
          case SDLK_SPACE:
          {
            std::cout << "FIRE!!!" << std::endl;
            ship -> fire();
            break;
          }
        }
      }
    }
  };
#include <iostream>
#include "SDL2/SDL.h"
using namespace std;

class Sprite{
public:
  Sprite(Uint32 color, int x, int y, int w = 48, int h = 64){
    image = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);

    SDL_FillRect(image, NULL, color);
    hitbox = image->clip_rect;
    hitbox.x = x;
    hitbox.y = y;
  }
  void update();
  void draw(SDL_Surface *dest){
    SDL_BlitSurface(image, NULL, dest, &hitbox);
  }
  void moveX(int x){
    hitbox.x += x;
  }
  void moveY(int y){
    hitbox.y += y;
  }

private:
  SDL_Surface *image;
  SDL_Rect hitbox;
  int originX, originY;
};

int main(){
  int fps = 60;
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window *win = SDL_CreateWindow("fds", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 900, 700, SDL_WINDOW_OPENGL);
  SDL_Surface *screen = SDL_GetWindowSurface(win);

  Uint32 red = SDL_MapRGB(screen->format, 255, 0, 0);
  Uint32 white = SDL_MapRGB(screen->format, 255, 255, 255);
  SDL_FillRect(screen, NULL, white);
  Sprite img(red, 100, 100);
  img.draw(screen);
  SDL_UpdateWindowSurface(win);
  SDL_Event event;
  Uint32 tick;
  int running = 1;
  while(running){
    tick = SDL_GetTicks();
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_QUIT){
        running = 0;
        break;
      }
      if(event.type == SDL_KEYDOWN){
        if(event.key.keysym.sym == SDLK_LEFT){
            img.moveX(-5);
        }
        if(event.key.keysym.sym == SDLK_RIGHT){
            img.moveX(5);
        }
        if(event.key.keysym.sym == SDLK_UP){
            img.moveY(-5);
        }
        if(event.key.keysym.sym == SDLK_DOWN){
            img.moveY(5);
        }
        break;
        }
      }

    SDL_FillRect(screen, NULL, white);
    img.draw(screen);
    SDL_UpdateWindowSurface(win);
    if((1000/fps) > SDL_GetTicks() - tick)
      SDL_Delay((1000/fps) > SDL_GetTicks() - tick);
  }


  SDL_DestroyWindow(win);

  SDL_Quit();

  return 0;
}

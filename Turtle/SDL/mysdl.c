#include <SDL.h>
#include <stdio.h>
#include "mysdl.h"

void sdl_start()
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0){
    ON_ERROR("SDL unable to initialise!\n");
  }
}

void fill_screen(SDL_Window* window, SDL_Surface* screen)
{
  screen = SDL_GetWindowSurface(window);
  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0)); /*From Lazy Foo -> Look up meanings*/
  SDL_UpdateWindowSurface(window);
}

void sdl_quit(SDL_Window* window, SDL_Renderer* renderer)
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void set_line(SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
}

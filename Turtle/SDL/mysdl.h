#include <SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 700
#define HALF_WIDTH 350
#define HALF_HEIGHT 350
#define ON_ERROR(STR) fprintf(stderr, "\n%s: %s\n", STR, SDL_GetError()); SDL_Quit(); exit(EXIT_FAILURE); /*Adapted from neillsdl2.h*/

void sdl_start();
void fill_screen(SDL_Window* window, SDL_Surface* screen);
void sdl_quit(SDL_Window* window, SDL_Renderer* renderer);
void set_line(SDL_Renderer* renderer);

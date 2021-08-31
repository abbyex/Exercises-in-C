#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>
#include "ext.h"
#include "SDL/mysdl.h"

int main(void)
{
  SDL_Window* window = NULL;
  SDL_Surface* screen = NULL;
  SDL_Renderer* renderer = NULL;
  SDL_Event event;
  SDL_bool done;

  turt t;
  stack *s;

  s = stack_init();
  init_struct(&t);
  while(file_read(&t) != false){
  }
  sdl_start();
  if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT,
    SDL_WINDOW_RESIZABLE, &window, &renderer) == 0){
      done = SDL_FALSE;
  }
    fill_screen(window, screen);
    while(done != SDL_TRUE){
       set_line(renderer);
       main_instr(&t, renderer, s);
         while (SDL_PollEvent(&event)){
             if (event.type == SDL_QUIT){
               done = SDL_TRUE;
               sdl_quit(window, renderer);
             }
         }

   if (t.fin == yes){
     printf("Parsed OK\n");
     SDL_Delay(1000);
     /*stack_free(s);*/
     SDL_DestroyRenderer(renderer);
     SDL_DestroyWindow(window);
     SDL_Quit();
     exit(0);
   }
 }
return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>
#include "interp.h"
#include "SDL/mysdl.h"

int main(int argc, char** argv)
{
  SDL_Window* window = NULL;
  SDL_Surface* screen = NULL;
  SDL_Renderer* renderer = NULL;
  SDL_Event event;
  SDL_bool done;

  FILE *fp;
  int i;
  turt t;
  stack *s;
  char* filename;
  (void)argc;

  s = stack_init();
  init_struct(&t);
  filename = argv[1];
  fp = fopen(filename,"r");
  if (fp == NULL)
  {
    ERROR("cannot open file");
  }
  i = 0;
  while (fscanf(fp, "%s", t.words[i])==1 && i<MAXMOVES){
    /*printf("%s\n", p.words[i]);*/
    i++;
  }
  assert(i<MAXMOVES);

  sdl_start();
  if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT,
    SDL_WINDOW_RESIZABLE, &window, &renderer) == 0){
      done = SDL_FALSE;
  }

  fill_screen(window, screen);
  while(!done){
    while (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT){
          done = SDL_TRUE;
          sdl_quit(window, renderer);
         }
    SDL_Delay(1000);
    set_line(renderer);
    main_instr(&t, renderer, s);
    if (t.fin == yes){
      printf("Parsed OK\n");
      SDL_Delay(10000);
      /*printf("%s\n", t.words[t.counter]);*/
      assert(is_end_bracket(&t) == true);
      fclose(fp);
      stack_free(s);
      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);
      SDL_Quit();
      exit(0);
     }
    }
   }
return 0;
}

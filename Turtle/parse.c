#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "parse.h"


int main(int argc, char** argv)
{
  FILE *fp;
  int i;
  prog p;
  char* filename;
  (void)argc;

  filename = argv[1];
  fp = fopen(filename,"r");
  if (fp == NULL)
  {
    ERROR("cannot open file");
  }

  i = 0;
  init_struct(&p);
  while (fscanf(fp, "%s", p.words[i])==1 && i<MAXMOVES){
    /*printf("%s\n", p.words[i]);*/
    i++;
  }
  assert(i<MAXMOVES);
  main_instr(&p);
  assert(is_end_bracket(&p) == true);
  assert(p.counter == i);
  printf("Parsed OK\n");
  fclose(fp);
  return 0;
}

#include "interp.h"
#include "SDL/mysdl.h"
#include "stack/stack.h"
#include <SDL.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void main_instr(turt *t, SDL_Renderer* renderer, stack *s)
{
  if(!strsame(t->words[t->counter], "{")){
    if (t->fin != yes){
      ERROR("Missing starting '{'");
    }
  }
  else
  {
  assert(is_start_bracket(t) == true);
  t->counter++;
  t->loops++;
  instr_list(t, renderer, s);
  }
}

void* instr_list(turt *t, SDL_Renderer* renderer, stack *s)
{
  while(!strsame(t->words[t->counter], "}")){
    if((instr(t, renderer, s) == true)){
      if(is_lower(t) == true){
        ERROR("Lower case not accepted as part of grammar");
      }
    }
  else {
  ERROR("Couldn't find next instruction");
    }
  }
  t->array_pos = STARTING_VAL;
  t->fin = yes;
  return NULL;
}

bool instr(turt *t, SDL_Renderer* renderer, stack *s)
{
  if((strsame(t->words[t->counter], "FD")) ||
  (strsame(t->words[t->counter], "RT")) ||
  (strsame(t->words[t->counter], "LT"))){
    /*printf("* %s\n", t->words[t->counter]);*/
    t->counter++;
    t->instruct++;
    if(varnum(t) == true){
      /*printf("* %s\n", t->words[t->counter]);*/
      if(var(t) == true){
        if(find_letter(t) == false){
          ERROR("Couldn't find the variable, has it been SET?");
        }
      }
      t->counter++;
      t->instruct++;
      execute_instruct(t, renderer);
      return true;
    }
    else if(varnum(t) == false) {
      ERROR("Couldn't find a variable");
    }
  }
  else if((set_loop(t, s)) == true){
    return true;
  }
  else if((do_loop(t) == true)){
    while (!(t->array[t->do_loop].cur_val >= t->array[t->do_loop].end_val)){
      t->instruct = STARTING_VAL;
      instr_list(t, renderer, s);
      t->counter = t->counter - t->instruct;
      t->array[t->do_loop].cur_val++;
    }
    t->do_loop = STARTING_VAL;
    return true;
  }
return false;
}


bool varnum(turt *t)
{
  if ((var(t) == true) || (num(t) == true)){
    return true;
  }
  return false;
}

bool num(turt *t)
{
  int i;
  if ((is_decimal(t) == false) || (is_negative(t) == false)){
    return false;
  }
  for (i = 0; i < MAXNUMSIZE; i++){
  if((isdigit(t->words[t->counter][i])) != false){
    return true;
  }
}
return false;
}
/* https://www.geeksforgeeks.org/isalpha-isdigit-functions-c-example/ */

bool var(turt *t)
{
  if((isalpha(t->words[t->counter][0])) != false){
    if(t->words[t->counter][1] == '\0'){
      if(is_lower(t) == true){
        ERROR("Lower case not accepted as part of grammar");
      }
      assert(isupper(t->words[t->counter][0]) != false);
      return true;
    }
  }
  return false;
}
/* https://www.geeksforgeeks.org/isalpha-isdigit-functions-c-example/ */

bool is_negative(turt *t)
{
  char negative;
  int i;
  negative = '-';
  for (i = 1; i < MAXNUMSIZE; i++){
    if((t->words[t->counter][i]) == negative){
    return false;
    }
  }
return true;
}

bool is_decimal(turt *t)
{
  char decimal;
  int i, deci_cnt;
  decimal = '.';
  deci_cnt = 0;
  for (i = 0; i < MAXNUMSIZE; i++){
    if((t->words[t->counter][i]) == decimal){
    deci_cnt++;
    if(deci_cnt > 1){
      return false;
      }
    }
  }
  return true;
}

void check_var(turt *t, char *c, int *a)
{
  if(find_letter(t) == false){
    create_letter(t, c);
  }
  else{
    get_pos(t, a);
    t->array_pos = *a;
  }
}

int num_var(turt *t, double *a)
{
  if(var(t) == true){
    get_val(t, a);
    return *a;
  }
  else if(num(t) == true){
  *a = atof(t->words[t->counter]);
  return *a;
  }
ERROR("Couldn't find a variable");
}

bool do_loop(turt *t)
{
  double a;
  int d;
  char* c;
  if(strsame(t->words[t->counter], "DO")){
    /*printf("* %s\n", t->words[t->counter]);*/
    t->counter++;
    if((var(t)) == true){
      /*printf("* %s\n", t->words[t->counter]);*/
      c = t->words[t->counter];
      check_var(t, c, &d);
      t->do_loop = t->array_pos;
      t->counter++;
      if(strsame(t->words[t->counter], "FROM")){
        /*printf("* %s\n", t->words[t->counter]);*/
        t->counter++;
        if((varnum(t)) == true){
          num_var(t, &a);
          /*printf("* %s\n", t->words[t->counter]);*/
          t->array[t->array_pos].cur_val = a;
          t->counter++;
          if(strsame(t->words[t->counter], "TO")){
            /*printf("* %s\n", t->words[t->counter]);*/
            t->counter++;
            if((varnum(t)) == true){
              num_var(t, &a);
              /*printf("* %s\n", t->words[t->counter]);*/
              t->array[t->array_pos].end_val = a;
              t->counter++;
              if(strsame(t->words[t->counter], "{")){
                t->counter++;
                t->loops++;
              return true;
              }
            }
            ERROR("Couldn't find a letter or number");
          }
        }
        ERROR("Couldn't find a letter or number");
      }
    }
  ERROR("Couldn't find a letter");
  }
return false;
}

bool set_loop(turt *t, stack *s)
{
  int d;
  double set_var;
  char* c;
  if(strsame(t->words[t->counter], "SET")){
    /*printf("* %s\n", t->words[t->counter]);*/
    t->counter++;
    t->instruct++;
    if((var(t)) == true){
      /*printf("* %s\n", t->words[t->counter]);*/
      c = t->words[t->counter];
      check_var(t, c, &d);
      t->counter++;
      t->instruct++;
      if(strsame(t->words[t->counter], ":=")){
        /*printf("* %s\n", t->words[t->counter]);*/
        t->counter++;
        t->instruct++;
        if((polish(t, s, &set_var) == true)){
          return true;
        }
        ERROR("Couldn't find a value to SET");
      }
    }
    ERROR("Couldn't find a letter");
  }
return false;
}

bool polish(turt *t, stack *s, double *set_var)
{
  double d;
  if(((is_instr(t)) == true)){
    return false;
  }
  if(op_func(t, s) == true){
    /*printf("* %s\n", t->words[t->counter]);*/
    t->counter++;
    t->instruct++;
    polish(t, s, set_var);
    return true;
  }
  else if(strsame(t->words[t->counter], ";")){
    stack_pop(s, set_var);
    t->array[t->array_pos].cur_val = *set_var;
    /*printf("* %s\n", t->words[t->counter]);*/
    t->counter++;
    t->instruct++;
    return true;
  }
  else if(varnum(t) == true){
    num_var(t, &d);
  }
  stack_push(s, &d);
    /*printf("* %s\n", t->words[t->counter]);*/
    t->counter++;
    t->instruct++;
    polish(t, s, set_var);
    return true;
}


bool op_func(turt *t, stack *s)
{
  double g1, g2, d;
  if(is_op(t) == false){
    return false;
  }
  if ((stack_pop(s, &g2) != true) || (stack_pop(s, &g1) != true)){
    ERROR("Couldn't SET the value of the variable");
  }
  if(strsame(t->words[t->counter], "+")){
      d = g1 + g2;
  }
  else if(strsame(t->words[t->counter], "-")){
      d = g1 - g2;
  }
  else if(strsame(t->words[t->counter], "*")){
      d = g1 * g2;
  }
  else if(strsame(t->words[t->counter], "/")){
      d = g1 / g2;
  }
  else {
    ERROR("Couldn't find an operator");
  }
  t->array[t->array_pos].cur_val = d;
  stack_push(s, &d);
  return true;
}



bool is_instr(turt *t)
{
  if((strsame(t->words[t->counter], "FD")) ||
  (strsame(t->words[t->counter], "LT")) ||
  (strsame(t->words[t->counter], "RT")) ||
  (strsame(t->words[t->counter], "DO")) ||
  (strsame(t->words[t->counter], "SET"))){
    return true;
  }
  return false;
}

bool is_num(turt *t)
{
  if((isdigit(t->words[t->counter][0])) != false){
    return true;
  }
  return false;
}
/* https://www.geeksforgeeks.org/isalpha-isdigit-functions-c-example/ */


bool is_letter(turt *t)
{
    if((isalpha(t->words[t->counter][0])) != false){
      return true;
    }
    return false;
}
/* https://www.geeksforgeeks.org/isalpha-isdigit-functions-c-example/ */

bool is_end_bracket(turt *t)
{
  if(strsame(t->words[t->counter], "}")){
    return true;
  }
  return false;
}


bool is_start_bracket(turt *t)
{
  if (strsame(t->words[t->counter], "{")){
    return true;
  }
  return false;
}

bool is_lower(turt *t)
{
  if (is_letter(t) == true){
    if((islower(t->words[t->counter][0])) != false){
      return true;
    }
  }
  return false;
}

bool is_op(turt *t)
{
  if((strsame(t->words[t->counter], "+")) ||
  (strsame(t->words[t->counter], "-")) ||
  (strsame(t->words[t->counter], "*")) ||
  (strsame(t->words[t->counter], "/"))){
    return true;
  }
  return false;
}




void create_letter(turt *t, char* c)
{
  if (find_letter(t) == false){
  t->array_pos = t->l_counter;
  t->array[t->l_counter].c = c;
  t->array[t->l_counter].cur_val = 0;
  t->array[t->l_counter].end_val = 0;
  t->array[t->l_counter].array_pos = t->l_counter;
  t->l_counter++;
  }
  else{
    update_letter(t);
  }
}

int get_pos(turt *t, int *a)
{
  int i;
  if(find_letter(t) == true){
    for (i = 0; i < ALPHA; i++){
      if (strsame(t->array[i].c, t->words[t->counter])){
        *a = i;
        return *a;
      }
    }
  }
  *a = NOT_FOUND;
  return *a;
}

void update_letter(turt *t)
{
  int a;
  get_pos(t, &a);
  t->array[a].cur_val = 0;
  t->array[a].end_val = 0;
  t->array_pos = a;
}

bool find_letter(turt *t)
{
  int i;
  for (i = 0; i < ALPHA; i++){
    if (strsame(t->array[i].c, t->words[t->counter])){
      return true;
    }
  }
  return false;
}

double get_val(turt *t, double *a)
{
  int i;
  for (i = 0; i < ALPHA; i++){
    if (strsame(t->array[i].c, t->words[t->counter])){
      *a = t->array[i].cur_val;
      return *a;
    }
  }
  return NOT_FOUND;
}

void init_struct(turt *t)
{

  int i;
  char* c;
  c = "0";
  t->angle = 0;
  t->cur_x = HALF_WIDTH;
  t->cur_y = HALF_HEIGHT;
  t->counter = 0;
  t->loops = 0;
  t->fin = no;
  for (i=0;i<MAXMOVES;i++){
    t->words[i][0] = '0';
    t->words[i][1] = '0';
  }
  t->do_loop = 0;
  t->instruct = 0;
  t->l_counter = 0;
  t->array_pos = 0;
  for(i=0; i<ALPHA; i++){
    t->array[i].c = c;
    t->array[i].cur_val = 0;
    t->array[i].end_val = 0;
  }
}

void forward(turt *t, double *a)
{
  double r_angle;
  r_angle = (t->angle * (M_PI / 180)); /*Convert from degree -> radian*/
  t->new_x = t->cur_x + ((*a) * sin(r_angle));
  t->new_y = t->cur_y - ((*a) * cos(r_angle));
}

void reset_coord(turt *t)
{
  t->cur_x = t->new_x;
  t->cur_y = t->new_y;
}

void right(turt *t, double *a)
{
  t->angle = t->angle + *a;
}

void left(turt *t, double *a)
{
  t->angle = t->angle - *a;
}

void execute_instruct(turt *t, SDL_Renderer* renderer)
{
   double number;
   int two;
   t->counter--;
   if (varnum(t) == true){
     num_var(t, &number);
   }
   t->counter++;
   two = t->counter - 2;
   if(strsame(t->words[two], "FD")){
     forward(t, &number);
     draw_line(renderer, t);
     reset_coord(t);
   }
   if(strsame(t->words[two], "LT")){
     left(t, &number);
   }
   if(strsame(t->words[two], "RT")){
     right(t, &number);
   }
}


void draw_line(SDL_Renderer* renderer, turt *t)
{
    SDL_RenderDrawLine(renderer, t->cur_x, t->cur_y, t->new_x, t->new_y);
    SDL_RenderPresent(renderer);
}

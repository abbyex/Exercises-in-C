#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "parse.h"

void main_instr(prog *p)
{
  if(!strsame(p->words[p->counter], "{")){
    MISSING("starting '{'");
  }
  /*printf("%s\n", p->words[p->counter]);*/
  assert(is_start_bracket(p) == true);
  p->counter++;
  p->loops++;
  instr_list(p);
}

void* instr_list(prog *p)
{
  while(!strsame(p->words[p->counter], "}")){
    if((instr(p) == true)){
      if(is_lower(p) == true){
        ERROR("lower case is not accepted as part of grammar");
      }
    }
  else {
  ERROR("next instruction not found");
    }
  }
  return NULL;
}

bool instr(prog *p)
{
  if((strsame(p->words[p->counter], "FD")) ||
  (strsame(p->words[p->counter], "RT")) ||
  (strsame(p->words[p->counter], "LT"))){
    /*printf("%s\n", p->words[p->counter]);*/
    p->counter++;
    if(varnum(p) == true){
      /*printf("%s\n", p->words[p->counter]);*/
      p->counter++;
      return true;
    }
    else if(varnum(p) == false) {
      MISSING("a Number or Letter");
    }
  }
  else if((do_loop(p) == true)){
    main_instr(p);
    return true;
  }
  else if((set_loop(p)) == true){
    return true;
  }
return false;
}

bool do_loop(prog* p)
{
  if(strsame(p->words[p->counter], "DO")){
    /*printf("%s\n", p->words[p->counter]);*/
    p->counter++;
    if((var(p)) == true){
      /*printf("%s\n", p->words[p->counter]);*/
      p->counter++;
      if(strsame(p->words[p->counter], "FROM")){
        /*printf("%s\n", p->words[p->counter]);*/
        p->counter++;
        if((varnum(p)) == true){
          /*printf("%s\n", p->words[p->counter]);*/
          p->counter++;
          if(strsame(p->words[p->counter], "TO")){
            /*printf("%s\n", p->words[p->counter]);*/
            p->counter++;
            if((varnum(p)) == true){
              /*printf("%s\n", p->words[p->counter]);*/
              p->counter++;
              return true;
            }
            MISSING("a Number or Letter");
          }
        }
        MISSING("a Number or Letter");
      }
    }
  MISSING("a Letter");
  }
return false;
}

bool set_loop(prog *p)
{
  if(strsame(p->words[p->counter], "SET")){
    /*printf("%s\n", p->words[p->counter]);*/
    p->counter++;
    if((var(p)) == true){
      /*printf("%s\n", p->words[p->counter]);*/
      p->counter++;
      if(strsame(p->words[p->counter], ":=")){
        /*printf("%s\n", p->words[p->counter]);*/
        p->counter++;
        if((polish(p) == true)){
          return true;
        }
        MISSING("Polish");
      }
    }
  MISSING("a Letter");
  }
return false;
}


bool polish(prog *p)
{
  if(((is_instr(p)) == true)){
    return false;
  }
  if(varnum(p) == true){
    /*printf("%s\n", p->words[p->counter]);*/
    p->counter++;
    polish(p);
    return true;
  }
  if(op_func(p) == true){
    /*printf("%s\n", p->words[p->counter]);*/
    p->counter++;
    polish(p);
    return true;
  }
  else if(strsame(p->words[p->counter], ";")){
    /*printf("%s\n", p->words[p->counter]);*/
    p->counter++;
    return true;
  }
  return false;
}

bool op_func(prog *p)
{
  if((strsame(p->words[p->counter], "+")) ||
  (strsame(p->words[p->counter], "-")) ||
  (strsame(p->words[p->counter], "*")) ||
  (strsame(p->words[p->counter], "/"))){
    return true;
}
return false;
}

void init_struct(prog *p)
{
  int i;
  for (i=0;i<MAXMOVES;i++){
    p->words[i][0] = '0';
    p->words[i][1] = '0';
  }
  p->counter = 0;
  p->loops = 0;
}

bool varnum(prog *p)
{
  if ((var(p) == true) || (num(p) == true)){
    return true;
  }
  return false;
}

bool num(prog *p)
{
  int i;
  if ((is_decimal(p) == false) || (is_negative(p) == false)){
    return false;
  }
  for (i = 0; i < MAXNUMSIZE; i++){
  if((isdigit(p->words[p->counter][i])) != false){
    return true;
  }
}
return false;
}
/* https://www.geeksforgeeks.org/isalpha-isdigit-functions-c-example/ */

bool var(prog* p)
{
  if((isalpha(p->words[p->counter][0])) != false){
    if(p->words[p->counter][1] == '\0'){
      if(is_lower(p) == true){
        ERROR("lower case is not accepted as part of grammar");
      }
      assert(isupper(p->words[p->counter][0]) != false);
      return true;
    }
  }
  /*printf("VAR %c\n", p->words[p->counter][1]);*/
  return false;
}
/* https://www.geeksforgeeks.org/isalpha-isdigit-functions-c-example/ */


bool is_negative(prog *p)
{
  char negative;
  int i;
  negative = '-';
  for (i = 1; i < MAXNUMSIZE; i++){
    if((p->words[p->counter][i]) == negative){
    return false;
  }
}
return true;
}

bool is_decimal(prog *p)
{
  char decimal;
  int i, deci_cnt;
  decimal = '.';
  deci_cnt = 0;
  for (i = 0; i < MAXNUMSIZE; i++){
    if((p->words[p->counter][i]) == decimal){
    deci_cnt++;
    if(deci_cnt > 1){
      return false;
      }
    }
  }
  return true;
}



bool is_instr(prog* p)
{
  if((strsame(p->words[p->counter], "FD")) ||
  (strsame(p->words[p->counter], "LT")) ||
  (strsame(p->words[p->counter], "RT")) ||
  (strsame(p->words[p->counter], "DO")) ||
  (strsame(p->words[p->counter], "SET"))){
    return true;
  }
  return false;
}

bool is_num(prog* p)
{
  if((isdigit(p->words[p->counter][0])) != false){
    return true;
  }
  return false;
}
/* https://www.geeksforgeeks.org/isalpha-isdigit-functions-c-example/ */


bool is_letter(prog* p)
{
    if((isalpha(p->words[p->counter][0])) != false){
      return true;
    }
    return false;
}
/* https://www.geeksforgeeks.org/isalpha-isdigit-functions-c-example/ */

bool is_end_bracket(prog* p)
{
int count;
count = 0;
while(strsame(p->words[p->counter], "}")){
  /*printf("%s\n", p->words[p->counter]);*/
  p->counter++;
  count++;
}
  if(count == p->loops)
  {
    return true;
  }
  else{
    MISSING("a closing '}'");
  }
  return false;
}


bool is_start_bracket(prog* p)
{
  if (strsame(p->words[p->counter], "{")){
    return true;
  }
  return false;
}

bool is_lower(prog *p)
{
  if (is_letter(p) == true){
    if((islower(p->words[p->counter][0])) != false){
      return true;
    }
  }
  return false;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"

#define STACKTYPE "Realloc"
#define SCALEFACTOR 2
#define FIXEDSIZE 16

/* Adapted from Neill's Stack Code on Github */
/* https://github.com/csnwc */ 

stack* stack_init(void)
{
   stack *s = (stack*) ncalloc(sizeof(stack), 1);
   /* Some implementations would allow you to pass
      a hint about the initial size of the stack */
   s->a = (double*) ncalloc(sizeof(double), FIXEDSIZE);
   s->size = 0;
   s->capacity= FIXEDSIZE;
   return s;
}

void stack_push(stack* s, double *d)
{
   if(s==NULL){
       return;
   }
   s->a[s->size] = *d;
   s->size = s->size + 1;
   if(s->size >= s->capacity){
      s->a = (double*) nremalloc(s->a, sizeof(double)*s->capacity*SCALEFACTOR);
      s->capacity = s->capacity*SCALEFACTOR;
   }
}

bool stack_pop(stack* s, double* d)
{
   if((s == NULL) || (s->size < 1)){
      return false;
   }
   s->size = s->size - 1;
   *d = s->a[s->size];
   return true;
}

bool stack_free(stack* s)
{
   if(s==NULL){
      return true;
   }
   free(s->a);
   free(s);
   return true;
}


void on_error(const char* s)
{
   fprintf(stderr, "%s\n", s);
   exit(EXIT_FAILURE);
}

void* nremalloc(void* p, int bytes)
{
   void* n = realloc(p, bytes);
   if(n==NULL){
      on_error("Cannot malloc() space");
   }
   return n;
}

void* ncalloc(int n, size_t size)
{
   void* v = calloc(n, size);
   if(v==NULL){
      on_error("Cannot calloc() space");
   }
   return v;
}

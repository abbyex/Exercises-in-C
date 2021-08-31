#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct stack stack;
typedef enum bool {false, true} bool;

struct stack {
   /* Underlying array */
   double* a;
   int size;
   int capacity;
};


/* Create an empty stack */
stack* stack_init(void);
/* Add element to top */
void stack_push(stack* s, double *d);
/* Take element from top */
bool stack_pop(stack* s, double* d);
/* Clears all space used */
bool stack_free(stack* s);

/* Optional? */

/* Copy top element into d (but don't pop it) */
/*bool stack_peek(stack*s,  stacktype* d);*/
/* Make a string version - keep .dot in mind */
/*void stack_tostring(stack*, char* str);*/

void on_error(const char* s);
void* ncalloc(int n, size_t size);
void* nremalloc(void* p, int bytes);

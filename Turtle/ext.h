#pragma once

#include <SDL.h>
#include "stack/stack.h"

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
#define MAXMOVES 10000
#define MAXNUMSIZE 20
#define ALPHA 26
#define NOT_FOUND -1
#define STARTING_VAL 0
#define FORMATSTR " "
#define strsame(A,B) (strcmp(A, B)==0) /* SOURCE: Neill's 01's example*/
#define ERROR(PHRASE, count) {fprintf(stderr, "Fatal Error, %s. Occured in input, line %d\n", PHRASE, count); exit(EXIT_FAILURE); }
#define MISSING(PHRASE, count) {fprintf(stderr, "Missing %s. Occured in input, line %d\n", PHRASE, count); exit(EXIT_FAILURE); }

typedef enum finished {no, yes} finished;

struct letter{
  char* c;
  double cur_val;
  double end_val;
  int array_pos;
};
typedef struct letter letter;

struct turt{
char words[MAXMOVES][MAXNUMSIZE];
int counter;
int loops;
double cur_x;
double cur_y;
double new_x;
double new_y;
int angle;
finished fin;
int instruct;
letter array[ALPHA];
int l_counter;
int array_pos;
int do_loop;
};
typedef struct turt turt;

void main_instr(turt *t, SDL_Renderer* renderer, stack *s);
void* instr_list(turt *t, SDL_Renderer* renderer, stack *s);
bool instr(turt *t, SDL_Renderer* renderer, stack *s);
bool varnum(turt *t);
bool var(turt *t);
bool num(turt *t);
bool do_loop(turt *t);
bool set_loop(turt *t, stack *s);
bool polish(turt *t, stack *s, double *set_var);
bool op_func(turt *t, stack *s);
bool is_decimal(turt *t);
bool is_negative(turt *t);

bool is_instr(turt *t);
bool is_num(turt *t);
bool is_letter(turt *t);
bool is_end_bracket(turt *t);
bool is_start_bracket(turt *t);
bool is_lower(turt *t);
bool is_op(turt *t);

void right(turt *t, double* a);
void left(turt *t, double* a);
void forward(turt *t, double *a);
void check_angle(turt *t);
void reset_coord(turt *t);
void init_struct(turt *t);
void create_letter(turt *t, char* c);
bool find_letter(turt *t);
double get_val(turt *t, double *a);
int get_pos(turt *t, int *a);
void update_letter(turt *t);
void reset_loop(turt *t, SDL_Renderer* renderer, stack *s);
int num_var(turt *t, double *a);
void check_var(turt *t, char *c, int *a);

void execute_instruct(turt *t, SDL_Renderer* renderer);
void draw_line(SDL_Renderer* renderer, turt *t);

bool file_read(turt *t);

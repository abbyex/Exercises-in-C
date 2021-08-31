#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "neillsimplescreen.h"

#define COL 80
#define ROW 30
#define EMPTY (char)0
#define TREE (char)64
#define FIRE (char)42

#define G 50
#define L 2500
#define PROBABILITY_L rand() % L
#define PROBABILITY_G rand() % G
#define ITERATIONS 1000
#define DISPLAY_TIME 0.05

typedef enum bool {false, true} bool;

void initArray(char r[ROW][COL]);
void fireToEmpty(char r[ROW][COL], int x, int y);
void inNeighbourhood(char r[ROW][COL], int x, int y);
void lightningStrike(char r[ROW][COL], int x, int y);
void treeGrowth(char r[ROW][COL], int x, int y);
bool inBoundary(int y, int x);
void printArray(char r[ROW][COL]);

void test();
void testInitArray(char r[ROW][COL]);
void testFireToEmpty(char r[ROW][COL]);
void testInNeighbourhood(char r[ROW][COL]);
void testLightningStrike(char r[ROW][COL]);
void testTreeGrowth(char r[ROW][COL]);
void testInBoundary(int y1, int x1, int y2, int x2);
bool flag;

int main(void)
{
   char r[ROW][COL];
   int count;
   test();
   initArray(r);
   neillclrscrn();

   for (count = 0; count<ITERATIONS; count++){
      neillcursorhome();
      printArray(r);
      neillbusywait(DISPLAY_TIME);
   }
   neillreset();

return 0;
}

/*Creates 2D initial array of 0's of size COL * ROW*/
void initArray(char r[ROW][COL])
{
   int y, x;
   printf("\n");
   for (x=0; x<ROW; x++){
      for (y=0; y<COL; y++){
         r[x][y] = EMPTY;
         printf("%c", r[x][y]);
      }
      printf("\n");
   }
   printf("\n");
}

/*A 'fire' cell will turn into an 'empty' cell on new grid*/
void fireToEmpty(char r[ROW][COL], int x, int y)
{
   if (r[x][y]== FIRE){
      r[x][y] = EMPTY;
      }
}


/*A tree within the 8-cell neighbourhood of a 'fire' cell becomes 'fire'*/
void inNeighbourhood(char r[ROW][COL], int x, int y)
{
   int i, j;
   flag = false;
   if (r[x][y] == FIRE){
      if (inBoundary(y, x) == true){
      flag = true;
      i = (y - 1); /* Starts in top-left corner of 8-neighbourhood*/
      j = (x - 1);
      for ( ; i < (y + 1) ; i++){ /* Checks cells NORTH -> SOUTH */
         for ( ; j < (x + 1) ; j++){ /* Checks cells EAST -> WEST */
            if (r[j][i] == TREE){
               r[j][i] = FIRE;
               }
         }
         if (r[j][i] == TREE){
            r[j][i] = FIRE;
            }
      }

      for ( ; i > (y - 1) ; i--){ /* Checks cells SOUTH -> NORTH */
         for ( ; j > (x - 1) ; j--){ /* Checks cells WEST -> EAST */
            if (r[j][i] == TREE){
               r[j][i] = FIRE;
               }
         }
         if (r[j][i] == TREE){
            r[j][i] = FIRE;
            }
         }
      }
      else{
        flag = false;
      }
   }
}

bool inBoundary(int y, int x)
{
   if(((y <= 0) || (y >= (COL - 1))) || ((x <= 0) || (x >= (ROW-1)))){
      return false;
      }
   return true;
}

/*A 'tree' is struck by lightning and catches 'fire' with probability 1 / L */
void lightningStrike(char r[ROW][COL], int x, int y)
{
   if (r[x][y] == TREE){
         if (PROBABILITY_L == 1){
            r[x][y] = FIRE;
            }
   }
}

/*An 'empty' cell will grow a 'tree' with probability of G */
void treeGrowth(char r[ROW][COL], int x, int y)
{
   if (r[x][y] == EMPTY){
         if (PROBABILITY_G == 1){
            r[x][y] = TREE;
            }
   }
}


void printArray(char r[ROW][COL])
{
   int y, x;
   printf("\n");
   for (x=0; x<ROW; x++){
      for (y=0; y<COL; y++){
         lightningStrike(r, x, y);
         treeGrowth(r, x, y);
         inNeighbourhood(r, x, y);
         if (r[x][y] == TREE){
           neillfgcol(green);
         }
         else if (r[x][y] == FIRE){
           neillfgcol(red);
         }
         printf("%c", r[x][y]);
         fireToEmpty(r, x, y);
      }
      printf("\n");
   }
   printf("\n");
}

void test()
{
   char r[ROW][COL];
   testInitArray(r);
   testFireToEmpty(r);
   testInNeighbourhood(r);
   testLightningStrike(r);
   testTreeGrowth(r);
   testInBoundary(-1, 25, 15, 31);
}

void testInitArray(char r[ROW][COL])
{
   initArray(r);
   assert((char)r[0][0] == EMPTY);
   assert((char)r[29][79] == EMPTY);
}

void testFireToEmpty(char r[ROW][COL])
{
   int y, x;
   for (x=0; x<ROW; x++){
      for (y=0; y<COL; y++){
         if (r[x][y] == FIRE){
            fireToEmpty(r, x, y);
            assert(r[x][y] == EMPTY);
         }
      }
   }
}

void testLightningStrike(char r[ROW][COL])
{
   int y, x;
   for (x=0; x<ROW; x++){
      for (y=0; y<COL; y++){
         if (r[x][y] == TREE){
            if (PROBABILITY_L == 1){
               lightningStrike(r, x, y);
               assert(r[x][y] == FIRE);
            }
         }
      }
   }
}

void testTreeGrowth(char r[ROW][COL])
{
   int y, x;
   for (x=0; x<ROW; x++){
      for (y=0; y<COL; y++){
         if (r[x][y] == EMPTY){
            if (PROBABILITY_G == 1){
               treeGrowth(r, x, y);
               assert((r[x][y] != FIRE) || (r[x][y] != EMPTY));
            }
         }
      }
   }
}

void testInBoundary(int y1, int x1, int y2, int x2)
{
  assert((inBoundary(y1, x1) == false) || (inBoundary(y2, x2) == false));
}

void testInNeighbourhood(char r[ROW][COL])
{
   int y, x;
   for (x=0; x<ROW; x++){
      for (y=0; y<COL; y++){
         inNeighbourhood(r, x, y);
            if (inBoundary(y, x) == false){
               assert(flag == false);
            }
      }
   }
}

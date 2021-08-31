#include <string.h>
#include <stdint.h>

typedef enum bool {false, true} bool;
typedef enum space {empty, full} space;

typedef struct hash {
  void* key;
  void* data;
  int array_index;
  space space;
} hash;

typedef struct assoc{
  struct hash* array;
  int size;
  int keysize;
  int capacity;
} assoc;

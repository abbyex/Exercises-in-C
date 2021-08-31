#include "specific.h"
#include "../assoc.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#define INITSZ 17
#define SCALEFACTOR 2
#define NOT_NEGATIVE -1
#define INCREMENT 1
#define RESIZE_VAL 0.6
#define SAME 0
#define STRING 0

void _create_new_cell(assoc** a, int* array_index);
bool _find_cell(assoc** a, void* key, int* array_index);
unsigned int _hash_function(unsigned char* key);
unsigned int _probe_function(assoc** a, int* increment_value, unsigned int* hash);
bool _is_prime(int* array_sz);
int _next_prime(assoc**a, int* number);
assoc** _realloc_array(assoc** a, assoc** a_new);


void _create_new_cell(assoc** a, int* array_index)
{
  int number;
  number = *array_index;
  (*a)->array[number].array_index = *array_index;
  (*a)->array[number].space = full;
  (*a)->capacity ++;
}

bool _find_cell(assoc** a, void* key, int* array_index)
{
  int keysz;
  keysz = (*a)->keysize;
  if (keysz == STRING){
    if ((strcmp(key, (*a)->array[*array_index].key)) == SAME){
      return true;
    }
  }
  else{
    if ((memcmp(key, (*a)->array[*array_index].key, keysz)) == SAME){
      return true;
    }
  }
  return false;
}

unsigned int _hash_function(unsigned char* key)
{
  unsigned char c;
  unsigned long hash = 5381;

  while((c = (*key++))){
    hash = ((hash << 5) + hash) + c;
  }
  return (unsigned int)hash;
  /* SOURCE:   http://www.cse.yorku.ca/~oz/hash.html */
}

unsigned int _probe_function(assoc** a, int* increment_value, unsigned int* hash)
{
  int array_sz;
  unsigned int probe;
  array_sz = (*a)->size;

  probe = ((*hash + ((*increment_value)*(*increment_value))) % array_sz);
  return (unsigned int)probe;
}

bool _is_prime(int* array_sz)
{
  int count;
  int n;
  n = *array_sz;
  for (count = 2; count < n; ++count){
      if (n % count == 0){
         return false;
      }
  }
  return true;
}

int _next_prime(assoc**a, int* number)
{
  int array_sz;
  array_sz = (*a)->size;
  *number = array_sz;
  *number = *number + ((*number)*SCALEFACTOR);
  while (_is_prime(number) == false){
    *number = *number + INCREMENT;
  }
  return *number;
}

assoc** _realloc_array(assoc** a, assoc** a_new)
{
  int i;
  int array_sz;
  int number;
  _next_prime(a, &number);
  array_sz = number;

  (*a_new) = (assoc *) ncalloc(1, sizeof(assoc));
  (*a_new)->array = (hash*) ncalloc(array_sz, sizeof(hash));
  (*a_new)->keysize = (*a)->keysize;
  (*a_new)->capacity = 0;
  (*a_new)->size = number;

  for (i = 0; i<array_sz; i++){
    (*a_new)->array->key = 0;
    (*a_new)->array->data = 0;
    (*a_new)->array->array_index = 0;
    (*a_new)->array->space = empty;
  }
  return a_new;
}


/*
   Initialise the Associative array
   keysize : number of bytes (or 0 => string)
   This is important when comparing keys since
   we'll need to use either memcmp() or strcmp()
*/
assoc* assoc_init(int keysize)
{
  assoc *a;
  int i;
  a = (assoc *) ncalloc(1, sizeof(assoc));
  a->array = (hash*) ncalloc(INITSZ, sizeof(hash));
  a->size = INITSZ;
  a->keysize = keysize;
  a->capacity = 0;

  for (i = 0; i<INITSZ; i++){
    a->array->key = 0;
    a->array->data = 0;
    a->array->array_index = 0;
    a->array->space = empty;
  }
  return a;
}



/* Free up all allocated space from 'a' */
void assoc_free(assoc* a)
{
   free(a->array);
   free(a);
}



/*
   Insert key/data pair
   - may cause resize, therefore 'a' might
   be changed due to a realloc() etc.
*/
void assoc_insert(assoc** a, void* key, void* data)
{
   assoc* a_new;
   int array_index;
   int array_sz;
   int array_cap;
   int increment_value;
   unsigned int hash;

  array_sz = (*a)->size;
  array_cap = (*a)->capacity;
  array_index = (*a)->array->array_index;
  increment_value = 1;

  if ((array_sz*RESIZE_VAL) < (array_cap)){
  array_index = 0;
    _realloc_array(a, &a_new);
    while(array_index < array_sz) {
      if ((*a)->array[array_index].space != empty){
        assoc_insert(&a_new, (*a)->array[array_index].key, (*a)->array[array_index].data);
      }
      array_index++;
  }
    assoc_free(*a);
    *a = a_new;
  }

  hash = _hash_function(key);
  array_index = (unsigned int)(hash%array_sz);
 if ((*a)->array[array_index].space == empty){
    (*a)->array[array_index].key = key;
    (*a)->array[array_index].data = data;
    _create_new_cell(a, &array_index);
  }
    if ((_find_cell(a, key, &array_index)) == true){
        (*a)->array[array_index].data = data;

    }
  else {
    while ((*a)->array[array_index].space == full){
      array_index = _probe_function(a, &increment_value, &hash);
      increment_value++;
    }
      (*a)->array[array_index].key = key;
      (*a)->array[array_index].data = data;
      _create_new_cell(a, &array_index);
     }
  }





/*
   Returns the number of key/data pairs
   currently stored in the table
*/
unsigned int assoc_count(assoc* a)
{
  return a->capacity;
}



/*
   Returns a pointer to the data, given a key
   NULL => not found
*/
void* assoc_lookup(assoc* a, void* key)
{
  int array_index;
  int increment_value;
  unsigned int hash;
  int array_sz;

  array_sz = a->size;
  increment_value = 1;
  array_index = 0;

  /*HASH FUNCTION*/
  hash = _hash_function(key);
  array_index = (unsigned int)(hash%array_sz);
  if ((a)->array[array_index].space == full){
    if (_find_cell(&a, key, &array_index) == true){
      return (a)->array[array_index].data;
    }
  }

  /*PROBE FUNCTION*/
  array_index = _probe_function(&a, &increment_value, &hash);
  if ((a)->array[array_index].space == full){
    if (_find_cell(&a, key, &array_index) == true){
      return (a)->array[array_index].data;
    }
  }

  while ((a)->array[array_index].space == full){
    if (_find_cell(&a, key, &array_index) == true){
      return (a)->array[array_index].data;
    }
    increment_value++;
    array_index = _probe_function(&a, &increment_value, &hash);
  }

  return NULL;
}

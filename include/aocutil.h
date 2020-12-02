#pragma once
#include <stdio.h>
#include <uthash.h>

/* Removes every element from the hashtable and calls free(3) on it
 * ty: Element type of the table
 * hashtable: The table
 */
#define CLEAR_AND_DELETE(ty, hashtable)\
  do {\
  ty *cur, *tmp;\
  HASH_ITER(hh, hashtable, cur, tmp) {          \
  HASH_DEL(hashtable, cur);\
  free(cur);\
  }\
  } while (0);


FILE *ensure_open(const char *path, const char *mode);

typedef struct hashable_int {
  int value;
  UT_hash_handle hh;
} hashable_int;

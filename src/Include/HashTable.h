#ifndef COSIVM_HASHTABLE_H
#define COSIVM_HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define COSIVM_HASHTABLE_KEY_LENGTH 10

typedef struct cosivm_ht_s {
  char key[COSIVM_HASHTABLE_KEY_LENGTH];
  long long value;

  struct cosivm_ht_s *next;
} cosivm_hashtable;

void cosivm_hashtable_init (cosivm_hashtable *);
int cosivm_hashtable_del (cosivm_hashtable *, char *);
cosivm_hashtable *cosivm_hashtable_tail (cosivm_hashtable *);
cosivm_hashtable *cosivm_hashtable_set (cosivm_hashtable *, char *, long long);
cosivm_hashtable *cosivm_hashtable_get (cosivm_hashtable *, char *);
void cosivm_hashtable_cleanup (cosivm_hashtable *);
void cosivm_hashtable_print (cosivm_hashtable *);

#endif


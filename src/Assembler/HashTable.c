#include "../Include/HashTable.h"

void cosivm_hashtable_init (cosivm_hashtable *h) {
  assert(h != NULL);

  h->next = NULL;
}

int cosivm_hashtable_del (cosivm_hashtable *h, char *key) {
  assert(h != NULL);
  assert(key != NULL);

  cosivm_hashtable *res = cosivm_hashtable_get(h, key);
  cosivm_hashtable *prev = h;

  // not found
  if (res == NULL)
    return -1;

  while (prev->next != res)
    prev = prev->next;

  prev->next = res->next;
  free(res);

  return 0;
}

cosivm_hashtable *cosivm_hashtable_tail (cosivm_hashtable *h) {
  assert(h != NULL);

  cosivm_hashtable *tail = h;

  while (tail->next != NULL)
    tail = tail->next;

  return tail;
}

cosivm_hashtable *cosivm_hashtable_set (cosivm_hashtable *h, char *key, long long value) {
  assert(h != NULL);
  assert(key != NULL);

  cosivm_hashtable *res = cosivm_hashtable_get(h, key);

  // exists
  if (res != NULL) {
    res->value = value;

    return res;
  }
  // does not exist
  else {
    cosivm_hashtable *tail = cosivm_hashtable_tail(h);
    tail->next = malloc(sizeof(*tail->next));
    if (tail->next == NULL)
      return NULL;	

    tail = tail->next;

    tail->value = value;
    tail->next = NULL;
    strncpy(tail->key, key, COSIVM_HASHTABLE_KEY_LENGTH);

    return tail;
  }
}

cosivm_hashtable *cosivm_hashtable_get (cosivm_hashtable *h, char *key) {
  assert(h != NULL);
  assert(key != NULL);

  cosivm_hashtable *res = h;

  while (strcmp(res->key, key) != 0) {
    if (res->next == NULL)
      return NULL;
    
    res = res->next;
  }

  return res;
}

void cosivm_hashtable_cleanup (cosivm_hashtable *h) {
  assert(h != NULL);

  cosivm_hashtable *tmp = h;
  cosivm_hashtable *cur;

  while (tmp != NULL) {
    cur = tmp->next;
    if (tmp != h)
      free(tmp);

    tmp = cur;
  }
}

void cosivm_hashtable_print (cosivm_hashtable *h) {
  assert(h != NULL);

  cosivm_hashtable *tmp = h;

  puts("{");

  while (tmp != NULL) {
    if (tmp != h)
      printf("%s: %lld,\n", tmp->key, tmp->value);

    tmp = tmp->next;
  }

  puts("}");
}

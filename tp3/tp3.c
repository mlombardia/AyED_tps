#include "tp3.h"

struct dictionary {};

dictionary_t *dictionary_create(destroy_f destroy) { return NULL; };

bool dictionary_put(dictionary_t *dictionary, const char *key, void *value) {
  return true;
};

void *dictionary_get(dictionary_t *dictionary, const char *key, bool *err) {
  return NULL;
};

bool dictionary_delete(dictionary_t *dictionary, const char *key) {
  return true;
};

void *dictionary_pop(dictionary_t *dictionary, const char *key, bool *err) {
  return NULL;
};

bool dictionary_contains(dictionary_t *dictionary, const char *key) {
  return true;
};

size_t dictionary_size(dictionary_t *dictionary) { return 0; };

void dictionary_destroy(dictionary_t *dictionary){};

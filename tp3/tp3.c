#include "tp3.h"

typedef struct {
  char *key;
  void *value;
} dictionary_slot_t;

struct dictionary {
  dictionary_slot_t **slots;
  size_t size;
  size_t count;
};

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
  int index = 0; //TODO: add hash fn
  dictionary_slot_t *slot = dictionary->slots[index];
  return slot != NULL && slot->key != NULL;
};

size_t dictionary_size(dictionary_t *dictionary) { return dictionary->count; };

void dictionary_destroy(dictionary_t *dictionary){
  for (size_t i = 0; i < dictionary->count; i++)
  {
    free(dictionary->slots[i]);
  }
  
};

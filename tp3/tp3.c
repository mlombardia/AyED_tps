#include "tp3.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define SIZE 100000
#define ALPHA 0.75

// https://www.programmingalgorithms.com/algorithm/fnv-hash/c/
unsigned int FNVHash(const char* str, unsigned int length) {
	const unsigned int fnv_prime = 0x811C9DC5;
	unsigned int hash = 0;
	unsigned int i = 0;

	for (i = 0; i < length; str++, i++)
	{
		hash *= fnv_prime;
		hash ^= (*str);
	}

	return hash;
}

struct dictionary_entry;
typedef struct dictionary_entry dictionary_entry_t;

struct dictionary_entry {
  char *key;
  void *value;
  dictionary_entry_t *next;
};

struct dictionary {
  dictionary_entry_t **slots;
  size_t size;
  size_t count;
  destroy_f destroy_fn;
};

unsigned int hash(dictionary_t *dictionary, const char *key){
  unsigned int prehash_value = FNVHash(key, (unsigned int)strlen(key));
  return prehash_value % (int) dictionary->size;
}

dictionary_t *dictionary_create(destroy_f destroy) {
  dictionary_t *dictionary = malloc(sizeof(dictionary_t));
  if (!dictionary)
  {
    return NULL;
  }
  
  dictionary->slots = calloc(SIZE, sizeof(dictionary_entry_t*));
  if (!dictionary->slots)
  {
    return NULL;
  }
  
  dictionary->size = SIZE;
  dictionary->count = 0;
  dictionary->destroy_fn = destroy;
  return dictionary;
}

bool dictionary_put(dictionary_t *dictionary, const char *key, void *value) {
  
  unsigned int index = hash(dictionary, key);

  if(dictionary->slots[index] == NULL){
    dictionary_entry_t *entry = malloc(sizeof(dictionary_entry_t));
    if(!entry){
      return false;
    }
    entry->key = malloc(strlen(key)+1);
    if (!entry->key){
      return false;
    }
    entry->key = strcpy(entry->key,key);
    entry->value = value;
    entry->next = NULL;
    dictionary->slots[index] = entry;
    dictionary->count++;
  } else {
    dictionary_entry_t *latest_entry = dictionary->slots[index];
    while(latest_entry->next != NULL && strcmp(latest_entry->key,key)!=0){
      latest_entry = latest_entry->next;
    }

    if (strcmp(latest_entry->key,key) == 0){
      if(latest_entry->key){
        dictionary->destroy_fn(latest_entry->value);
      }
      latest_entry->value = value;
    }else {
      dictionary_entry_t *entry = malloc(sizeof(dictionary_entry_t));
      if(!entry){
        return false;
      }
      entry->key = malloc(strlen(key)+1);
      if (!entry->key){
        return false;
      }
      entry->key = strcpy(entry->key,key);
      entry->value = value;
      entry->next = NULL;
      latest_entry->next = entry;
      dictionary->count++;
    }
  }

  if ((double)dictionary->count / (double)dictionary->size > ALPHA){
    dictionary_entry_t **slots = dictionary->slots;

    size_t previous_size = dictionary->size;
    dictionary->size += SIZE;
    dictionary->slots = calloc(dictionary->size, sizeof(dictionary_entry_t*));
    dictionary->count = 0;

    for (int i = 0; i < previous_size; i++){
      dictionary_entry_t *current = slots[i];
      while (current != NULL){
        dictionary_put(dictionary, current->key, current->value);
        dictionary_entry_t *temp = current;
        current = current->next;
        free(temp->key);
        free(temp);
      }
    }
    free(slots);
  }

  return true;
}

void *dictionary_get(dictionary_t *dictionary, const char *key, bool *err) {
  
  unsigned int index = hash(dictionary, key);
  dictionary_entry_t *entry = dictionary->slots[index];

  while (entry != NULL && strcmp(entry->key, key) != 0 ){
    entry = entry->next;
  }

  if (!entry || strcmp(entry->key, key) != 0)
  {
    *err=true;
    return NULL;
  }
  
  
  *err=false;
  return entry->value;
}

bool dictionary_delete(dictionary_t *dictionary, const char *key) {
  unsigned int index = hash(dictionary, key);

  dictionary_entry_t *current = dictionary->slots[index];
  dictionary_entry_t *previous = NULL;

  while (current != NULL && strcmp(current->key, key) != 0 ){
    previous = current;
    current = current->next;
  }

  if (previous == NULL){
    dictionary->slots[index] = current->next; 
  } else {
    previous->next = current->next;
  }
  
  free(current->key);
  if (dictionary->destroy_fn)
  {
    dictionary->destroy_fn(current->value);
  }
  free(current);
  dictionary->count--;

  return true;
};

void *dictionary_pop(dictionary_t *dictionary, const char *key, bool *err) {
  unsigned int index = hash(dictionary, key);

  dictionary_entry_t *current = dictionary->slots[index];
  dictionary_entry_t *previous = NULL;

  while (current != NULL && strcmp(current->key, key) != 0 ){
    previous = current;
    current = current->next;
  }

  if (!current)
  {
    *err = true;
    return NULL;
  }

  if (strcmp(current->key, key) != 0)
  {
    *err = true;
    return NULL;
  }
  
  if (previous == NULL){
    dictionary->slots[index] = current->next; 
  } else {
    previous->next = current->next;
  }
  
  void *value = current->value;

  free(current->key);
  free(current);
  dictionary->count--;

  *err = false;
  return value;
};

bool dictionary_contains(dictionary_t *dictionary, const char *key) {
  bool err;
  void *value = dictionary_get(dictionary, key, &err);
  return value != NULL;
};

size_t dictionary_size(dictionary_t *dictionary) { return dictionary->count; };

void dictionary_destroy(dictionary_t *dictionary){
  for (int i = 0; i < dictionary->size; i++){
    dictionary_entry_t *current = dictionary->slots[i];
    while (current != NULL){
      dictionary_entry_t *aux = current;
      current = current->next;
      free(aux->key);
      if (dictionary->destroy_fn)
      {
        dictionary->destroy_fn(aux->value);
      }
      
      free(aux);
    }
  }
  free(dictionary->slots);
  free(dictionary);
};

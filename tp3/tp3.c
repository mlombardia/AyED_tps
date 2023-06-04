#include "tp3.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define SIZE 10
//#define ALPHA 0.75

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

struct dictionary_slot;
typedef struct dictionary_slot dictionary_slot_t;

struct dictionary_slot {
  char *key;
  void *value;
  bool contains_NULL;
};

struct dictionary {
  dictionary_slot_t **slots;
  size_t size;
  size_t count;
  destroy_f destroy_fn;
};

int hash(dictionary_t *dictionary, const char *key){
  unsigned int prehash = FNVHash(key, (unsigned int)strlen(key));
  return (int) prehash % (int) dictionary->size;
}

bool slot_is_assigned(dictionary_slot_t *slot){
  return slot != NULL;
}

bool slot_contains_key(dictionary_slot_t *slot, const char *key){
  if (slot_is_assigned(slot))
  {
    return strcmp(slot->key,key) == 0;
  }
  return false;
}
dictionary_slot_t *find_slot(dictionary_t *dictionary, const char *key){
  int index = hash(dictionary, key);

  dictionary_slot_t *slot = dictionary->slots[index];
  
  while ((slot && strcmp(slot->key, key) != 0) && index < dictionary->count)
  {
    slot = dictionary->slots[++index];
  }

  if (!slot || strcmp(slot->key, key) != 0)
  {
    return NULL;
  }

  return slot;
}

// dictionary_t *resize_dictionary(dictionary_t *dictionary){
//   dictionary_t *new_dict = malloc(sizeof(dictionary_t));
//   if (!new_dict)
//   {
//     return NULL;
//   }
//   new_dict->size = dictionary->size + SIZE;
//   new_dict->slots = calloc(new_dict->size, sizeof(dictionary_slot_t *));
//   if (!new_dict->slots)
//   {
//     return NULL;
//   }
//   new_dict->count = 0;
//   new_dict->destroy_fn = dictionary->destroy_fn;
  
//   for (size_t i = 0; i < dictionary->size; i++)
//   {
//     if (slot_is_assigned(dictionary->slots[i]))
//     {
//       dictionary_put(new_dict, dictionary->slots[i]->key, dictionary->slots[i]->value);
//     }
//   }
  
//   return new_dict;
// }

dictionary_t *dictionary_create(destroy_f destroy) {
  dictionary_t *dictionary = malloc(sizeof(dictionary_t));
  if (!dictionary)
  {
    return NULL;
  }
  dictionary->size = SIZE;
  dictionary->slots = calloc(dictionary->size, sizeof(dictionary_slot_t *));
  if (!dictionary->slots)
  {
    return NULL;
  }
  dictionary->count = 0;
  dictionary->destroy_fn = destroy;
  
  return dictionary; 
  };

bool dictionary_put(dictionary_t *dictionary, const char *key, void *value) {

  // if (((float)dictionary->count/(float)dictionary->size) >= ALPHA)
  // {
  //   dictionary = resize_dictionary(dictionary);
  // }
  

  int index = hash(dictionary, key);

  bool is_assigned = slot_is_assigned(dictionary->slots[index]);
  
  while ( is_assigned && !slot_contains_key(dictionary->slots[index], key))
  {
    index++;
  }

  if (!is_assigned)
  {
    dictionary->slots[index] = malloc(sizeof(dictionary_slot_t));
    if (!dictionary->slots[index])
    {
      return false;
    }
    
    (dictionary->slots[index])->key = malloc(strlen(key)+1);
    
    if (!(dictionary->slots[index])->key)
    {
      return false;
    }

    strcpy((dictionary->slots[index])->key, key);
    
    (dictionary->slots[index])->value = value;
    (dictionary->slots[index])->contains_NULL = false;
    dictionary->count++;
  } else {
    if (dictionary->destroy_fn && (dictionary->slots[index])->value)
    {
      dictionary->destroy_fn((dictionary->slots[index])->value);
      //(dictionary->slots[index])->value = malloc(sizeof(void *));
    }
    (dictionary->slots[index])->value = value;
    (dictionary->slots[index])->contains_NULL = false;
  }

  return true;
};

void *dictionary_get(dictionary_t *dictionary, const char *key, bool *err) {
  dictionary_slot_t *slot = find_slot(dictionary, key);
  if (!slot || slot->value == NULL)
  {
    *err = true;
    return NULL;
  }
  
  *err=false;
  return slot->value;
};

bool dictionary_delete(dictionary_t *dictionary, const char *key) {
  dictionary_slot_t *slot = find_slot(dictionary, key);
  if (!slot)
  {
    return false;
  }

  free(slot->value);
  free(slot->key);

  slot->key = NULL;

  free(slot);
  slot = NULL;

  dictionary->count--;
  return true;
};

void *dictionary_pop(dictionary_t *dictionary, const char *key, bool *err) {
  dictionary_slot_t *slot = find_slot(dictionary, key);
  if (!slot)
  {
    *err = true;
    return NULL;
  }

  if (!slot->value)
  {
    *err = true;
    return NULL;
  }
  

  void *value = slot->value;

  slot->value = NULL;
  slot->contains_NULL = true;

  *err = false;
  return value;
};

bool dictionary_contains(dictionary_t *dictionary, const char *key) {
  dictionary_slot_t *slot = find_slot(dictionary, key);
  if (!slot)
  {
    return false;
  }
  return slot != NULL && slot->key != NULL && strcmp(slot->key, key) == 0;
};

size_t dictionary_size(dictionary_t *dictionary) { return dictionary->count; };

void dictionary_destroy(dictionary_t *dictionary){
  for (int i = 0; i < dictionary->size; i++)
  {

    if (slot_is_assigned(dictionary->slots[i]))
    {
      free(dictionary->slots[i]->key);
    }
    

    free(dictionary->slots[i]);
  }
  free(dictionary->slots);
  free(dictionary);
};

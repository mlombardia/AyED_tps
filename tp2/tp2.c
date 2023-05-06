#include "tp2.h"
#include <stdlib.h>
#include <stdbool.h>

struct node;
typedef struct node node_t;

struct node {
    void* value;
    node_t* next;
    node_t* prev;
};

struct list {
    node_t* head;
    node_t* tail;
    size_t size;
};

struct list_iter {
    list_t* list;
    node_t* curr;
};

list_t *list_new(){
  list_t *list = malloc(sizeof(list_t));
  if (list)
  {
    list->size=0;
    list->head=NULL;
    list->tail=NULL;
    return list;
  }
  return NULL;
}

size_t list_length(const list_t *list){
    return list->size;
}

bool list_is_empty(const list_t *list){
    return list->size <= 0;
}

bool list_insert_head(list_t *list, void *value){
  node_t *aux = malloc(sizeof(node_t));
  if (!aux)
  {
    return false;
  }
  aux->value = value;
  aux->next = list->head;
  aux->prev = NULL;

  if (!list->head)
  {
    list->tail = aux;
    list->head = list->tail;
    list->size++;
    return true;
  }
  
  list->head->prev = aux;
  list->head = aux;
  list->size++;
  return true;
}

bool list_insert_tail(list_t *list, void *value){
  node_t *aux = malloc(sizeof(node_t));
  if (!aux)
  {
    return false;
  }
  aux->value = value;
  aux->next = NULL;
  aux->prev = list->tail;

  if (!list->tail)
  {
    list->tail = aux;
    list->head = list->tail;
    list->size++;
    return true;
  }
  
  list->tail->next = aux;
  list->tail = aux;
  list->size++;
  return true;
}

void *list_peek_head(const list_t *list){
  if (!list || !list->head)
  {
    return NULL;
  }
  
  return list->head->value;
}

void *list_peek_tail(const list_t *list){
    if (!list || !list->tail)
  {
    return NULL;
  }
  
  return list->tail->value;
}

void *list_pop_head(list_t *list){
  node_t *aux = NULL;
  if (list->size == 0)
  {
    return NULL;
  }

  aux = list->head;
  int *value = aux->value;

  if (list->head == list->tail)
  {
    list->head = NULL;
    list->tail = NULL;
    list->size--;

    return value;
  }
  
  list->head = list->head->next;
  list->head->prev = NULL;
  list->size--;

  free(aux);

  return value;
}

void *list_pop_tail(list_t *list){
  node_t *aux = NULL;
  if (list->size == 0)
  {
    return NULL;
  }

  aux = list->tail;
  int *value = aux->value;
  if (list->head == list->tail)
  {
    list->head = NULL;
    list->tail = NULL;
    list->size--;
    return aux->value;
  }

  list->tail = list->tail->prev;
  list->tail->next = NULL;
  list->size--;

  free(aux);

  return value;
}

void list_destroy(list_t *list, void destroy_value(void *)){
  if (destroy_value)
  {
    while (list->head != list->tail)
    {
        node_t *aux = list->head;
        list->head = list->head->next;
        destroy_value(aux);
    }
    destroy_value(list->head);
  }
  free(list);
}

list_iter_t *list_iter_create_head(list_t *list){
  list_iter_t *iter = malloc(sizeof(list_iter_t));
  if (!iter)
  {
    return NULL;
  }
  iter->list = list;
  iter->curr = list->head;
  
  return iter;
}

list_iter_t *list_iter_create_tail(list_t *list){
  list_iter_t *iter = malloc(sizeof(list_iter_t));
  if (!iter)
  {
    return NULL;
  }
  iter->list = list;
  iter->curr = list->tail;
  
  return iter;
}

bool list_iter_forward(list_iter_t *iter){
  if (!iter->curr || !iter->curr->next)
  {
    return false;
  }
  
  iter->curr = iter->curr->next;
  return true;
}

bool list_iter_backward(list_iter_t *iter){
  if (!iter->curr || !iter->curr->prev)
  {
    return false;
  }
  
  iter->curr = iter->curr->prev;
  return true;
}

void *list_iter_peek_current(const list_iter_t *iter){
  if (list_is_empty(iter->list))
  {
    return NULL;
  }
  
  return iter->curr->value;
}

bool list_iter_at_last(const list_iter_t *iter){
    return list_is_empty(iter->list) || iter->curr == iter->list->tail;
}

bool list_iter_at_first(const list_iter_t *iter){
    return list_is_empty(iter->list) || iter->curr == iter->list->head;
}

void list_iter_destroy(list_iter_t *iter){
  free(iter);
}

bool list_iter_insert_after(list_iter_t *iter, void *value){
  node_t *node = malloc(sizeof(node_t));
  if (!node)
  {
    return false;
  }

  if (list_is_empty(iter->list))
  {
    if(!list_insert_head(iter->list, value)){
      return false;
    };
    return true;
  }
  
  
  node->value = value;
  node->next = iter->curr->next;
  node->prev = iter->curr;
  if (iter->curr == iter->list->tail)
  {
    iter->curr->next = node;
    iter->list->tail = iter->curr->next;
  }else
  {
    iter->curr->next->prev = node;
    iter->curr->next = node;
  }
  iter->list->size++;
  return true;
}

bool list_iter_insert_before(list_iter_t *iter, void *value){
  node_t *node = malloc(sizeof(node_t));
  if (!node)
  {
    return false;
  }

  if (list_is_empty(iter->list))
  {
    if(!list_insert_head(iter->list, value)){
      return false;
    };
    return true;
  }

  node->value = value;
  node->next = iter->curr;
  node->prev = iter->curr->prev;
  if (!list_iter_at_first(iter))
  {
    iter->curr->prev->next = node;
  }
  iter->curr->prev = node;
  if (iter->curr == iter->list->head)
  {
    iter->list->head = iter->curr->prev;
  }
  
  iter->list->size++;
  return true;
}

void *list_iter_delete(list_iter_t *iter){
  if (list_is_empty(iter->list))
  {
    return NULL;
  }

  if (list_iter_at_last(iter))
  {
    int* value = list_pop_tail(iter->list);
    iter->curr = iter->list->tail;
    return value;
  }
  
  if (list_iter_at_first(iter))
  {
    int* value = list_pop_head(iter->list);
    iter->curr = iter->list->head;
    return value;
  }
  
  
  node_t *aux = iter->curr;
  int *value = aux->value;
  iter->curr->next->prev = aux->prev;
  iter->curr->prev->next = aux->next;
  if (aux->next)
  {
    iter->curr = aux->next;
  } else
  {
    iter->curr = aux->prev;
  }
  
  
  iter->list->size--;
  free(aux);
  return value;
}
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
  if (!list->head)
  {
    list->head = malloc(sizeof(node_t));
    if(!list->head){
      return false;
    }
    list->head->next=NULL;
    list->head->prev=NULL;
    list->head->value=value;
    list->tail = list->head;
    list->size++;
    return true;
  } else {
    node_t *aux = malloc(sizeof(node_t));
    if (!aux)
    {
      return false;
    }
    aux->value = value;
    aux->next = list->head;
    aux->prev = NULL;
    list->head = aux;
    list->size++;
    return true;
  }
  
  return false;
}

bool list_insert_tail(list_t *list, void *value){
  if (!list->tail)
  {
    list->tail = malloc(sizeof(node_t));
    if(!list->tail){
      return false;
    }
    list->tail->next=NULL;
    list->tail->prev=NULL;
    list->tail->value=value;
    list->head = list->tail;
    list->size++;
    return true;
  } else {
    node_t *aux = malloc(sizeof(node_t));
    if (!aux)
    {
      return false;
    }
    aux->value = value;
    aux->next = NULL;
    aux->prev = list->tail;
    list->tail = aux;
    list->size++;
    return true;
  }
  
  return false;
}

void *list_peek_head(const list_t *list){
  if (!list)
  {
    return NULL;
  }
  
  return list->head;
}

void *list_peek_tail(const list_t *list){
    if (!list)
  {
    return NULL;
  }
  
  return list->head;
}

void *list_pop_head(list_t *list){
    return NULL;
}

void *list_pop_tail(list_t *list){
    return NULL;
}

void list_destroy(list_t *list, void destroy_value(void *)){
  // if (destroy_value)
  // {
  //   /* code */
  // }
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
  if (!iter->curr->next)
  {
    return false;
  }
  
  iter->curr = iter->curr->next;
  return true;
}

bool list_iter_backward(list_iter_t *iter){
  if (!iter->curr->prev)
  {
    return false;
  }
  
  iter->curr = iter->curr->prev;
  return true;
}

void *list_iter_peek_current(const list_iter_t *iter){
  if (is_empty(iter->list))
  {
    return NULL;
  }
  
  return iter->curr;
}

bool list_iter_at_last(const list_iter_t *iter){
    return list_is_empty(iter->list) || iter->curr == iter->list->head;
}

bool list_iter_at_first(const list_iter_t *iter){
    return list_is_empty(iter->list) || iter->curr == iter->list->tail;
}

void list_iter_destroy(list_iter_t *iter){
    return;
}

bool list_iter_insert_after(list_iter_t *iter, void *value){
    return false;
}

bool list_iter_insert_before(list_iter_t *iter, void *value){
    return false;
}

void *list_iter_delete(list_iter_t *iter){
    return NULL;
}
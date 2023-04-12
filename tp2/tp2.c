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
    list->head->next = NULL;
    list->head->prev = NULL;
    list->head->value=value;
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
    list->tail->next = NULL;
    list->tail->prev = NULL;
    list->tail->value=value;
    if (list->head)
    {
      list->head->next = NULL;
      list->tail->prev = list->tail;
    }
    
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
  node_t *aux;
  if (list->size == 0)
  {
    return NULL;
  }

  if (list->head)
  {
    aux = list->head;
    list->head = list->head->next;
  }

  return aux->value;
}

void *list_pop_tail(list_t *list){
  node_t *aux;
  if (list->size == 0)
  {
    return NULL;
  }

  if (list->tail)
  {
    aux = list->tail;
    list->tail = list->tail->prev;
  }

  return aux->value;
}

void list_destroy(list_t *list, void destroy_value(void *)){
  int count = 0;
  printf("entro a if\n");
  if (destroy_value)
  {
    printf("entro a while\n");
    while (list->head != list->tail)
    {
      if (list->head)
      {
        printf("%d\n", count);
        printf("Borro elem\n");
        node_t *aux = list->head;
        list->head = list->head->next;
        destroy_value(aux);
        count++;
      }

      if (list->tail)
      {
        printf("%d\n", count);
        printf("Borro elem\n");
        node_t *aux = list->tail;
        list->tail = list->head->prev;
        destroy_value(aux);
        count++;
      }
    }

    if (list->head)
    {
      destroy_value(list->head);
    }

    if (list->tail)
    {
      destroy_value(list->tail);
    }
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
  if (list_is_empty(iter->list))
  {
    return NULL;
  }
  
  return iter->curr->value;
}

bool list_iter_at_last(const list_iter_t *iter){
    return list_is_empty(iter->list) || iter->curr == iter->list->head;
}

bool list_iter_at_first(const list_iter_t *iter){
    return list_is_empty(iter->list) || iter->curr == iter->list->tail;
}

void list_iter_destroy(list_iter_t *iter){
  free(iter);
}

bool list_iter_insert_after(list_iter_t *iter, void *value){
  node_t *node = malloc(sizeof(node_t));
  node->value = value;
  node->next = iter->curr->next;
  node->prev = iter->curr;
  iter->curr->next = node;
  return true;
}

bool list_iter_insert_before(list_iter_t *iter, void *value){
  node_t *node = malloc(sizeof(node_t));
  node->value = value;
  node->next = iter->curr;
  node->prev = iter->curr->prev;
  iter->curr->prev = node;
  return true;
}

void *list_iter_delete(list_iter_t *iter){
  node_t *aux = iter->curr;
  iter->curr->next->prev = aux->prev;
  iter->curr->prev->next = aux->next;
  return aux->value;
}
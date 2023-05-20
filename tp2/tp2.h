#include <stdbool.h>
#include <stdio.h>

#ifndef TP2_H
#define TP2_H

struct list;
typedef struct list list_t;
struct iterator;
typedef struct list_iter list_iter_t;

/*
 * Crea una nueva lista.
 * Devuelve NULL si falla.
 */
list_t *list_new(void);

/*
 * Devuelve TRUE si la lista está vacia.
 * Pre-condiciones: La lista existe.
 */
bool list_is_empty(const list_t *list);

/*
 * Devuelve el largo de la lista.
 * Pre-condiciones: La lista existe.
 */
size_t list_length(const list_t *list);

/*
 * Inserta un elemento al principio de la lista.
 * Pre-condiciones: La lista existe.
 * Post-condiciones: Devuelve TRUE si funcionó y insertó un elemento.
 */
bool list_insert_head(list_t *list, void *value);

/*
 * Inserta un elemento al final de la lista.
 * Pre-condiciones: La lista existe.
 * Post-condiciones: Devuelve TRUE si funcionó y insertó un elemento.
 */
bool list_insert_tail(list_t *list, void *value);

/*
 * Elimina un elemento del principio de la lista y devuelve el puntero al dato que almacenaba.
 * Pre-condiciones: La lista existe.
 * Post-condiciones: Devuelve el dato y saca un nodo del principio de la lista
 * si la lista no está vacia. Devuelve NULL si está vacia.
 */
void *list_pop_head(list_t *list);

/*
 * Elimina un elemento del final de la lista y devuelve el puntero al dato que almacenaba.
 * Pre-condiciones: La lista existe.
 * Post-condiciones: Devuelve el dato y saca un nodo del final de la lista
 * si la lista no está vacia. Devuelve NULL si está vacia.
 */
void *list_pop_tail(list_t *list);

/*
 * Devuelve el puntero al dato que está en el principio de la lista.
 * Pre-condiciones: La lista existe.
 * Post-condiciones: Devuelve el primer valor de la lista, NULL si la lista está vacia.
 */
void *list_peek_head(const list_t *list);

/*
 * Devuelve el puntero al dato que está en el final de la lista.
 * Devuelve NULL si la lista está vacia.
 * Pre-condiciones: La lista existe.
 * Post-condiciones: Devuelve el último valor de la lista, NULL si la lista está vacia.
 */
void *list_peek_tail(const list_t *list);

/*
 * Destruye una lista liberando toda su memoria. Recibe por parametro una función para liberar a sus miembros.
 * Pre-condiciones: La lista existe.
 * Post-condiciones: La memoria de la lista está liberada junto con la de sus elementos.
 * El puntero a lista ya no puede usarse. Si la función es NULL no la utiliza.
 */
void list_destroy(list_t *list, void destroy_value(void *));

/*
 * Primitivas de iterador externo
 */

/*
 * Devuelve un nuevo iterador
 * Pre: La lista está creada
 * Post: El iterador está en el principio de la lista. Devuelve NULL si falla.
 */
list_iter_t *list_iter_create_head(list_t *list);

/*
 * Devuelve un nuevo iterador
 * Pre: La lista está creada
 * Post: El iterador está en el final de la lista. Devuelve NULL si falla.
 */
list_iter_t *list_iter_create_tail(list_t *list);

/*
 * Avanza el iterador una posición
 * Pre: El iterador está creado
 * Post: El iterador avanza una posición. Si no puede avanzar más devuelve false, sino true.
 */
bool list_iter_forward(list_iter_t *iter);

/*
 * Avanza el iterador una posición hacia atras
 * Pre: El iterador está creado
 * Post: El iterador va una posición hacia atras. Si no puede devuelve false, sino true.
 */
bool list_iter_backward(list_iter_t *iter);

/*
 * Devuelve el valor en la posición actual.
 * Pre: El iterador está creado
 * Post: Devuelve NULL si la lista está vacia, sino el valor.
 */
void *list_iter_peek_current(const list_iter_t *iter);

/*
 * Evalua si el iterador está al final
 * Pre: El iterador está creado
 * Post: Devuelve true si el iterador está al final, sino false.
 * Si la lista está vacia es true.
 */
bool list_iter_at_last(const list_iter_t *iter);

/*
 * Evalua si el iterador está al principio
 * Pre: El iterador está creado
 * Post: Devuelve true si el iterador está al principio, sino false.
 * Si la lista está vacia es true.
 */
bool list_iter_at_first(const list_iter_t *iter);

/*
 * Destruye el iterador externo
 * Pre: El iterador fue creado
 * Post: El iterador está destruido
 */
void list_iter_destroy(list_iter_t *iter);

/*
 * Agrega un elemento despues del elemento actual del iterador.
 * Pre: El iterador fue creado
 * Post: Agrega un nuevo elemento despues del actual en la lista. Devuelve true si tuvo éxito.
 * No altera la posición del iterador. Devuelve false si falla.
 */
bool list_iter_insert_after(list_iter_t *iter, void *value);

/*
 * Agrega un elemento antes del elemento actual del iterador.
 * Pre: El iterador fue creado
 * Post: Agrega un nuevo elemento antes del actual en la lista. Devuelve true si tuvo éxito.
 * No altera la posición del iterador. Devuelve false si falla.
 */
bool list_iter_insert_before(list_iter_t *iter, void *value);

// Takes away the iterator's current position's data from the list
// Pre: The iterator and the list have been created

/*
 * Elimina un elemento del iterador
 * Pre: El iterador fue creado
 * Post: Elimina el elemento actual del iterador y se posiciona en el siguiente.
 * De no existir el siguiente, se posiciona en el anterior.
 * Devuelve el valor contenido por el eliminado, si la lista está vacia devuelve NULL.
 */
void *list_iter_delete(list_iter_t *iter);

#endif
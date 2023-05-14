#include "test_malloc.h"
#include "tp2.h"
#include "testing.h"
#include <stdbool.h>
#include <stdlib.h>

bool test_create_and_destroy_list() {
    bool tests_result = true;
    list_t* list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    list_destroy(list, NULL);
    return tests_result;
}

bool test_create_with_failed_malloc() {
    bool tests_result = true;
    set_malloc_status(false);
    list_t* list = list_new();
    set_malloc_status(true);
    tests_result &= test_assert("La lista no fue creada", list == NULL);
    return tests_result;
}

bool test_empty_size_and_length() {
    bool tests_result = true;
    list_t* list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    tests_result &= test_assert("El largo de la lista es 0", list_length(list) == 0);
    tests_result &= test_assert("La lista está vacia", list_is_empty(list));
    list_destroy(list, NULL);
    return tests_result;
}

bool test_insert_head_successfully() {
    bool tests_result = true;
    list_t* list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    tests_result &= test_assert("El largo de la lista es 0", list_length(list) == 0);
    tests_result &= test_assert("La lista está vacia", list_is_empty(list));
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_head(list, NULL));
    tests_result &= test_assert("El largo de la lista es 1", list_length(list) == 1);
    tests_result &= test_assert("La lista no está vacia", !list_is_empty(list));
    list_destroy(list, NULL);
    return tests_result;
}

bool test_insert_head_fails() {
    bool tests_result = true;
    list_t* list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    tests_result &= test_assert("El largo de la lista es 0", list_length(list) == 0);
    set_malloc_status(false);
    tests_result &= test_assert("Falló insertar un elemento en la lista", !list_insert_head(list, NULL));
    set_malloc_status(true);
    tests_result &= test_assert("El largo de la lista es 0", list_length(list) == 0);
    tests_result &= test_assert("Luego de fallar vuelve a funcionar insertar", list_insert_head(list, NULL));
    tests_result &= test_assert("El largo de la lista es 1", list_length(list) == 1);
    list_destroy(list, NULL);
    return tests_result;
}

bool test_destroy_value() {
    bool tests_result = true;
    bool insert_status = true;
    list_t* list = list_new();
    for(int i=0; i<100; i++){
        int* aux = malloc(sizeof(int));
        *aux = i;
        insert_status &= list_insert_head(list, aux);
    }
    tests_result &= test_assert("Se insertaron 100 elementos en la lista", insert_status);
    list_destroy(list, free);
    test_assert("Se destruyo la lista", true);
    return tests_result;
}

bool test_insert_tail_successfully() {
    bool tests_result = true;
    list_t* list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    tests_result &= test_assert("El largo de la lista es 0", list_length(list) == 0);
    tests_result &= test_assert("La lista está vacia", list_is_empty(list));
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, NULL));
    tests_result &= test_assert("El largo de la lista es 1", list_length(list) == 1);
    tests_result &= test_assert("La lista no está vacia", !list_is_empty(list));
    list_destroy(list, NULL);
    return tests_result;
}

bool test_insert_tail_fails() {
    bool tests_result = true;
    list_t* list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    tests_result &= test_assert("El largo de la lista es 0", list_length(list) == 0);
    set_malloc_status(false);
    tests_result &= test_assert("Falló insertar un elemento en la lista", !list_insert_tail(list, NULL));
    set_malloc_status(true);
    tests_result &= test_assert("El largo de la lista es 0", list_length(list) == 0);
    tests_result &= test_assert("Luego de fallar vuelve a funcionar insertar", list_insert_tail(list, NULL));
    tests_result &= test_assert("El largo de la lista es 1", list_length(list) == 1);
    list_destroy(list, NULL);
    return tests_result;
}

bool test_peek_head() {
    bool tests_result = true;
    list_t* list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    tests_result &= test_assert("EL valor de head es NULL con la lista vacia", !list_peek_head(list));
    for(int i=0;i<10;i++){
        int* aux = malloc(sizeof(int));
        *aux = i;
        list_insert_head(list, aux);
        tests_result &= test_assert("El valor de head es correcto",
                                    *((int*)list_peek_head(list)) == i);
    }
    list_destroy(list, free);
    return tests_result;
}

bool test_peek_tail() {
    bool tests_result = true;
    list_t* list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    tests_result &= test_assert("EL valor de head es NULL con la lista vacia", !list_peek_tail(list));
    for(int i=0;i<10;i++){
        int* aux = malloc(sizeof(int));
        *aux = i;
        list_insert_tail(list, aux);
        tests_result &= test_assert("El valor de head es correcto",
                                    *((int*)list_peek_tail(list)) == i);
    }
    list_destroy(list, free);
    return tests_result;
}

bool test_pop_empty_list() {
    bool tests_result = true;
    list_t *list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    tests_result &= test_assert("La salida de pop head es NULL", !list_pop_head(list));
    tests_result &= test_assert("La salida de pop tail es NULL", !list_pop_tail(list));
    list_destroy(list, NULL);
    return tests_result;
}

bool test_simple_pop_head() {
    bool tests_result = true;
    list_t *list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    int* aux = malloc(sizeof(int));
    *aux = 42;
    tests_result &= test_assert("Se inserto un elemento en el principio de la lista", list_insert_head(list, aux));
    tests_result &= test_assert("El largo de la lista es 1", list_length(list) == 1);
    tests_result &= test_assert("Al eliminar el head el valor es correcto", *((int*)list_pop_head(list)) == 42);
    tests_result &= test_assert("No hay más elementos en la lista", !list_pop_head(list));
    tests_result &= test_assert("El largo de la lista es 0", list_length(list) == 0);
    tests_result &= test_assert("Se inserto un elemento en el final de la lista", list_insert_tail(list, aux));
    tests_result &= test_assert("El largo de la lista es 1", list_length(list) == 1);
    tests_result &= test_assert("Al eliminar el head el valor es correcto", *((int*)list_pop_head(list)) == 42);
    tests_result &= test_assert("No hay más elementos en la lista", !list_pop_head(list));
    tests_result &= test_assert("El largo de la lista es 0", list_length(list) == 0);
    free(aux);
    list_destroy(list, NULL);
    return tests_result;
}

bool test_simple_pop_tail() {
    bool tests_result = true;
    list_t *list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    int* aux = malloc(sizeof(int));
    *aux = 42;
    tests_result &= test_assert("Se inserto un elemento en el principio de la lista", list_insert_tail(list, aux));
    tests_result &= test_assert("El largo de la lista es 1", list_length(list) == 1);
    tests_result &= test_assert("Al eliminar el tail el valor es correcto", *((int*)list_pop_tail(list)) == 42);
    tests_result &= test_assert("No hay más elementos en la lista", !list_pop_tail(list));
    tests_result &= test_assert("El largo de la lista es 0", list_length(list) == 0);
    tests_result &= test_assert("Se inserto un elemento en el final de la lista", list_insert_head(list, aux));
    tests_result &= test_assert("El largo de la lista es 1", list_length(list) == 1);
    tests_result &= test_assert("Al eliminar el tail el valor es correcto", *((int*)list_pop_tail(list)) == 42);
    tests_result &= test_assert("No hay más elementos en la lista", !list_pop_tail(list));
    tests_result &= test_assert("El largo de la lista es 0", list_length(list) == 0);
    free(aux);
    list_destroy(list, NULL);
    return tests_result;
}

bool test_multiple_peek() {
    bool tests_result = true;
    list_t *list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    for(int i=0;i<10;i++){
        int* aux = malloc(sizeof(int));
        *aux = i;
        if (i % 2 ==0){
            tests_result &= test_assert("Se inserto un número al principio", list_insert_head(list, aux));
            tests_result &= test_assert("El valor de head es el insertado",
                                        *((int*)list_peek_head(list)) == i);
            if(list_length(list) > 1) {
                tests_result &= test_assert("El valor de tail es correcto",
                                            *((int *) list_peek_tail(list)) == (i - 1));
            } else {
                tests_result &= test_assert("El valor de tail es correcto",
                                            *((int *) list_peek_tail(list)) == i);
            }
        } else {
            tests_result &= test_assert("Se inserto un número al final", list_insert_tail(list, aux));
            tests_result &= test_assert("El valor de head es correcto",
                                        *((int*)list_peek_head(list)) == (i-1));
            tests_result &= test_assert("El valor de tail es el insertado",
                                        *((int*)list_peek_tail(list)) == i);

        }
    }
    list_destroy(list, free);
    return tests_result;
}

bool test_multiple_pop() {
    bool tests_result = true;
    list_t *list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    for(int i=0;i<100;i++){
        int* aux = malloc(sizeof(int));
        *aux = i;
        list_insert_head(list, aux);
        list_insert_tail(list, aux);
    }

    tests_result &= test_assert("El largo de la lista es 200", list_length(list) == 200);

    for(int i=99;i>=0;i--){
        int* aux = list_pop_head(list);
        tests_result &= test_assert("Eliminar el primer elemento funciona correctamente", *((int*)aux) == i);
        tests_result &= test_assert("Eliminar el último elemento funciona correctamente", (int*)list_pop_tail(list) == aux);
        free(aux);
    }

    tests_result &= test_assert("La lista está vacia", list_is_empty(list));

    list_destroy(list, NULL);
    return tests_result;
}

bool test_multiple_pop_random_patterns() {
    bool tests_result = true;
    list_t *list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    for(int i=0;i<100;i++){
        int* aux = malloc(sizeof(int));
        *aux = i;
        list_insert_head(list, aux);
        list_insert_tail(list, aux);
        switch(rand() % 4){
            case 0:
                list_insert_head(list, aux);
                list_insert_tail(list, aux);
                tests_result &= test_assert("Eliminar el primer elemento funciona correctamente", *((int*)list_pop_head(list)) == i);
                tests_result &= test_assert("Eliminar el último elemento funciona correctamente", *((int*)list_pop_tail(list)) == i);
                break;

            case 1:
                tests_result &= test_assert("Eliminar el primer elemento funciona correctamente", *((int*)list_pop_head(list)) == i);
                tests_result &= test_assert("Eliminar el último elemento funciona correctamente", *((int*)list_pop_tail(list)) == i);
                list_insert_head(list, aux);
                list_insert_tail(list, aux);
                break;

            case 2:
                tests_result &= test_assert("Eliminar el último elemento funciona correctamente", *((int*)list_pop_tail(list)) == i);
                list_insert_head(list, aux);
                tests_result &= test_assert("Eliminar el primer elemento funciona correctamente", *((int*)list_pop_head(list)) == i);
                list_insert_tail(list, aux);
                break;

            case 3:
                tests_result &= test_assert("Eliminar el primer elemento funciona correctamente", *((int*)list_pop_head(list)) == i);
                list_insert_head(list, aux);
                tests_result &= test_assert("Eliminar el último elemento funciona correctamente", *((int*)list_pop_tail(list)) == i);
                list_insert_tail(list, aux);
                break;
        }
    }

    tests_result &= test_assert("El largo de la lista es 200", list_length(list) == 200);

    for(int i=99;i>=0;i--){
        int* aux = list_pop_head(list);
        tests_result &= test_assert("Eliminar el primer elemento funciona correctamente", *((int*)aux) == i);
        tests_result &= test_assert("Eliminar el último elemento funciona correctamente", (int*)list_pop_tail(list) == aux);
        free(aux);
    }

    tests_result &= test_assert("La lista está vacia", list_is_empty(list));

    list_destroy(list, NULL);
    return tests_result;
}

bool test_multiple_random_failed_operations() {
    bool tests_result = true;
    list_t *list1 = list_new();
    tests_result &= test_assert("La lista 1 fue creada", list1 != NULL);
    list_t *list2 = list_new();
    tests_result &= test_assert("La lista 2 fue creada", list2 != NULL);
    int* aux = NULL, *aux2 = NULL;
    for(int i=0;i<300;i++) {
        switch(rand() % 12) {
            case 0: // insert head exitoso
                aux = malloc(sizeof(int));
                *aux = i;
                list_insert_head(list1, aux);
                list_insert_head(list2, aux);
            case 1: //insert head fallido
                set_malloc_status(false);
                list_insert_head(list1, aux);
                set_malloc_status(true);
            case 2: // insert tail exitoso
                aux = malloc(sizeof(int));
                *aux = i;
                list_insert_tail(list1, aux);
                list_insert_tail(list2, aux);
            case 3: //insert tail fallido
                set_malloc_status(false);
                list_insert_tail(list1, aux);
                set_malloc_status(true);
            case 4: //pop head
                aux = list_pop_head(list1);
                if(aux){
                    free(aux);
                }
                list_pop_head(list2);
            case 5: //pop tail
                aux = list_pop_tail(list1);
                if(aux){
                    free(aux);
                }
                list_pop_tail(list2);
            default:
                aux = malloc(sizeof(int));
                *aux = i;
                list_insert_head(list1, aux);
                list_insert_head(list2, aux);
        }
        tests_result &= test_assert("El estado de las listas es correcto",
                                    (list_length(list1) == list_length(list2)) &&
                                            (list_peek_head(list1) == list_peek_head(list2)) &&
                                            (list_peek_tail(list1) == list_peek_tail(list2)));
    }
    for(int i=0;i < list_length(list1) / 2;i++){
        switch(rand() % 6) {
            case 0:
                aux = list_pop_head(list1);
                aux2 = list_pop_head(list2);
                tests_result &= test_assert("El valor extraido de las listas es correcto", aux == aux2);
                free(aux);
            case 1: //insert head fallido
                aux = list_pop_tail(list1);
                aux2 = list_pop_tail(list2);
                tests_result &= test_assert("El valor extraido de las listas es correcto", aux == aux2);
                free(aux);
        }
    }
    list_destroy(list1, free);
    list_destroy(list2, NULL);
    return tests_result;
}

bool test_iter_create_and_destroy() {
    bool tests_result = true;
    list_t* list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    list_iter_t* iter = list_iter_create_head(list);
    list_iter_t* iter2 = list_iter_create_tail(list);
    tests_result &= test_assert("El iterador en head fue creado", iter != NULL);
    tests_result &= test_assert("El iterador en tail fue creado", iter2 != NULL);
    list_iter_destroy(iter);
    list_iter_destroy(iter2);
    list_destroy(list, NULL);
    return tests_result;
}

bool test_iter_create_with_failed_malloc() {
    bool tests_result = true;
    list_t* list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    set_malloc_status(false);
    list_iter_t* iter = list_iter_create_head(list);
    list_iter_t* iter2 = list_iter_create_tail(list);
    set_malloc_status(true);
    tests_result &= test_assert("El iterador en head no fue creado", iter == NULL);
    tests_result &= test_assert("El iterador en tail no fue creado", iter2 == NULL);
    list_destroy(list, NULL);
    return tests_result;
}

bool test_iter_empty_list_move_fails() {
    bool tests_result = true;
    list_t* list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    list_iter_t* iter = list_iter_create_head(list);
    list_iter_t* iter2 = list_iter_create_tail(list);
    tests_result &= test_assert("El iterador en head fue creado", iter != NULL);
    tests_result &= test_assert("El iterador en tail fue creado", iter2 != NULL);
    tests_result &= test_assert("El iterador en head no puede avanzar", !list_iter_forward(iter));
    tests_result &= test_assert("El iterador en head no puede retroceder", !list_iter_backward(iter));
    tests_result &= test_assert("El iterador en tail no puede avanzar", !list_iter_forward(iter2));
    tests_result &= test_assert("El iterador en tail no puede retroceder", !list_iter_backward(iter2));
    list_iter_destroy(iter);
    list_iter_destroy(iter2);
    list_destroy(list, NULL);
    return tests_result;
}

bool test_iter_one_element_list_move_fails() {
    bool tests_result = true;
    list_t* list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, &list));
    list_iter_t* iter = list_iter_create_head(list);
    list_iter_t* iter2 = list_iter_create_tail(list);
    tests_result &= test_assert("El iterador en head fue creado", iter != NULL);
    tests_result &= test_assert("El iterador en tail fue creado", iter2 != NULL);
    tests_result &= test_assert("El iterador en head no puede avanzar", !list_iter_forward(iter));
    tests_result &= test_assert("El iterador en head no puede retroceder", !list_iter_backward(iter));
    tests_result &= test_assert("El iterador en tail no puede avanzar", !list_iter_forward(iter2));
    tests_result &= test_assert("El iterador en tail no puede retroceder", !list_iter_backward(iter2));
    list_iter_destroy(iter);
    list_iter_destroy(iter2);
    list_destroy(list, NULL);
    return tests_result;
}

bool test_iter_simple_move() {
    bool tests_result = true;
    list_t* list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    int* aux = malloc(sizeof(int));
    *aux = 1;
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, aux));
    aux = malloc(sizeof(int));
    *aux = 2;
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, aux));
    list_iter_t* iter = list_iter_create_head(list);
    tests_result &= test_assert("El iterador en head fue creado", iter != NULL);
    tests_result &= test_assert("El iterador en head avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El iterador en head no puede volver a avanzar", !list_iter_forward(iter));
    tests_result &= test_assert("El iterador en head retrocedio", list_iter_backward(iter));
    tests_result &= test_assert("El iterador en head no puede volver a retroceder", !list_iter_backward(iter));
    list_iter_destroy(iter);
    list_destroy(list, free);
    return tests_result;
}

bool test_iter_peek_empty_list() {
    bool tests_result = true;
    list_t* list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    list_iter_t* iter = list_iter_create_head(list);
    tests_result &= test_assert("El iterador en head fue creado", iter != NULL);
    tests_result &= test_assert("El valor del actual del iterador es NULL", !list_iter_peek_current(iter));
    list_iter_destroy(iter);
    list_destroy(list, free);
    return tests_result;
}

bool test_iter_move_and_peek() {
    bool tests_result = true;
    list_t* list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    int* aux = malloc(sizeof(int));
    *aux = 1;
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, aux));
    aux = malloc(sizeof(int));
    *aux = 2;
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, aux));
    list_iter_t* iter = list_iter_create_head(list);
    tests_result &= test_assert("El iterador en head fue creado", iter != NULL);
    tests_result &= test_assert("El valor del actual del iterador es 1",
                                *((int*)list_iter_peek_current(iter)) == 1);
    tests_result &= test_assert("El iterador en head avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El valor del actual del iterador es 2",
                                *((int*)list_iter_peek_current(iter)) == 2);
    tests_result &= test_assert("El iterador en head retrocedio", list_iter_backward(iter));
    tests_result &= test_assert("El valor del actual del iterador es 1",
                                *((int*)list_iter_peek_current(iter)) == 1);
    list_iter_destroy(iter);
    list_destroy(list, free);
    return tests_result;
}

bool test_iter_move_at_start_and_end() {
    bool tests_result = true;
    list_t* list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    int* aux = malloc(sizeof(int));
    *aux = 1;
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, aux));
    aux = malloc(sizeof(int));
    *aux = 2;
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, aux));
    list_iter_t* iter = list_iter_create_head(list);
    tests_result &= test_assert("El iterador en head fue creado", iter != NULL);
    tests_result &= test_assert("El iterador esta al principio", list_iter_at_first(iter));
    tests_result &= test_assert("El iterador no esta al final", !list_iter_at_last(iter));
    tests_result &= test_assert("El iterador en head avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El iterador no esta al principio", !list_iter_at_first(iter));
    tests_result &= test_assert("El iterador esta al final", list_iter_at_last(iter));
    tests_result &= test_assert("El iterador en head retrocedio", list_iter_backward(iter));
    tests_result &= test_assert("El iterador esta al principio", list_iter_at_first(iter));
    tests_result &= test_assert("El iterador no esta al final", !list_iter_at_last(iter));
    list_iter_destroy(iter);
    list_destroy(list, free);
    return tests_result;
}

bool test_iter_full_list_read_only() {
    bool tests_result = true;
    list_t* list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    for(int i=1; i<=100; i++){
        int* aux = malloc(sizeof(int));
        *aux = i;
        tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, aux));
    }
    list_iter_t* iter = list_iter_create_head(list);
    tests_result &= test_assert("El iterador en head fue creado", iter != NULL);
    tests_result &= test_assert("El iterador esta al principio", list_iter_at_first(iter));
    tests_result &= test_assert("El iterador no esta al final", !list_iter_at_last(iter));
    int i=1;
    tests_result &= test_assert("El valor del actual del iterador es correcto",
                                *((int*)list_iter_peek_current(iter)) == i);
    while(list_iter_forward(iter)){
        i++;
        tests_result &= test_assert("Se avanzo una posicion y el valor del actual del iterador es correcto",
                                    *((int*)list_iter_peek_current(iter)) == i);
    }
    tests_result &= test_assert("El iterador no esta al principio", !list_iter_at_first(iter));
    tests_result &= test_assert("El iterador esta al final", list_iter_at_last(iter));
    i=100;
    tests_result &= test_assert("El valor del actual del iterador es correcto",
                                *((int*)list_iter_peek_current(iter)) == i);
    while(list_iter_backward(iter)){
        i--;
        tests_result &= test_assert("Se avanzo una posicion y el valor del actual del iterador es correcto",
                                    *((int*)list_iter_peek_current(iter)) == i);
    }
    tests_result &= test_assert("El iterador esta al principio", list_iter_at_first(iter));
    tests_result &= test_assert("El iterador no esta al final", !list_iter_at_last(iter));
    list_iter_destroy(iter);
    list_destroy(list, free);
    return tests_result;
}

bool test_iter_move_on_random_list() {
    bool tests_result = true;
    list_t* list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    int* aux = NULL;
    for(int i=0;i<300;i++) {
        switch(rand() % 6) {
            case 0: // insert head exitoso
                aux = malloc(sizeof(int));
                *aux = i;
                list_insert_head(list, aux);
            case 1: // insert tail exitoso
                aux = malloc(sizeof(int));
                *aux = i;
                list_insert_tail(list, aux);
            case 2: //pop head
                aux = list_pop_head(list);
                if(aux){
                    free(aux);
                }
            case 3: //pop tail
                aux = list_pop_tail(list);
                if(aux){
                    free(aux);
                }
            default:
                aux = malloc(sizeof(int));
                *aux = i;
                list_insert_head(list, aux);
        }
    }
    list_iter_t* iter = list_iter_create_tail(list);
    tests_result &= test_assert("El iterador en tail fue creado", iter != NULL);
    tests_result &= test_assert("El iterador no esta al principio", !list_iter_at_first(iter));
    tests_result &= test_assert("El iterador esta al final", list_iter_at_last(iter));
    int cant=1;
    while(list_iter_backward(iter)) {
        cant++;
    }
    tests_result &= test_assert("El largo de la lista es consistente con la cantidad iterada",
                                list_length(list) == cant);
    tests_result &= test_assert("El iterador esta al principio", list_iter_at_first(iter));
    tests_result &= test_assert("El iterador no esta al final", !list_iter_at_last(iter));
    list_iter_destroy(iter);
    list_destroy(list, free);
    return tests_result;
}

bool test_iter_insert_after_at_start() {
    bool tests_result = true;
    list_t* list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    int* aux = malloc(sizeof(int));
    *aux = 1;
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, aux));
    aux = malloc(sizeof(int));
    *aux = 3;
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, aux));
    list_iter_t* iter = list_iter_create_head(list);
    tests_result &= test_assert("El iterador en head fue creado", iter != NULL);
    aux = malloc(sizeof(int));
    *aux = 2;
    tests_result &= test_assert("Se inserto un elemento delante de head", list_iter_insert_after(iter, aux));
    tests_result &= test_assert("El iterador sigue en el primero", list_iter_at_first(iter));
    list_iter_destroy(iter);

    iter = list_iter_create_head(list);
    tests_result &= test_assert("Se creo un nuevo iterador al principio", iter != NULL);
    tests_result &= test_assert("El elemento actual es 1",
                                *((int*)list_iter_peek_current(iter)) == 1);
    tests_result &= test_assert("El iterador avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El elemento actual es 2",
                                *((int*)list_iter_peek_current(iter)) == 2);
    tests_result &= test_assert("El iterador avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El elemento actual es 3",
                                *((int*)list_iter_peek_current(iter)) == 3);
    tests_result &= test_assert("El iterador no puede avanzar", !list_iter_forward(iter));
    list_iter_destroy(iter);

    aux = list_pop_head(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 1", *aux == 1);
    free(aux);
    aux = list_pop_head(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 2", *aux == 2);
    free(aux);
    aux = list_pop_head(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 3", *aux == 3);
    free(aux);
    list_destroy(list, free);
    return tests_result;
}

bool test_iter_insert_after_at_start_fails() {
    bool tests_result = true;
    list_t* list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    int* aux = malloc(sizeof(int));
    *aux = 1;
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, aux));
    aux = malloc(sizeof(int));
    *aux = 3;
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, aux));
    list_iter_t* iter = list_iter_create_head(list);
    tests_result &= test_assert("El iterador en head fue creado", iter != NULL);
    set_malloc_status(false);
    tests_result &= test_assert("Fallo insertar un elemento delante", !list_iter_insert_after(iter, aux));
    set_malloc_status(true);
    tests_result &= test_assert("El iterador sigue en el primero", list_iter_at_first(iter));
    list_iter_destroy(iter);

    aux = list_pop_head(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 1", *aux == 1);
    free(aux);
    aux = list_pop_head(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 3", *aux == 3);
    free(aux);
    list_destroy(list, free);
    return tests_result;
}

bool test_iter_insert_after_at_middle() {
    bool tests_result = true;
    list_t* list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    int* aux = malloc(sizeof(int));
    *aux = 1;
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, aux));
    aux = malloc(sizeof(int));
    *aux = 2;
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, aux));
    aux = malloc(sizeof(int));
    *aux = 4;
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, aux));
    list_iter_t* iter = list_iter_create_head(list);
    tests_result &= test_assert("El iterador en head fue creado", iter != NULL);
    tests_result &= test_assert("El iterador avanzo", list_iter_forward(iter));
    aux = malloc(sizeof(int));
    *aux = 3;
    tests_result &= test_assert("Se inserto un elemento delante", list_iter_insert_after(iter, aux));
    list_iter_destroy(iter);

    iter = list_iter_create_head(list);
    tests_result &= test_assert("Se creo un nuevo iterador al principio", iter != NULL);
    tests_result &= test_assert("El elemento actual es 1",
                                *((int*)list_iter_peek_current(iter)) == 1);
    tests_result &= test_assert("El iterador avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El elemento actual es 2",
                                *((int*)list_iter_peek_current(iter)) == 2);
    tests_result &= test_assert("El iterador avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El elemento actual es 3",
                                *((int*)list_iter_peek_current(iter)) == 3);
    tests_result &= test_assert("El iterador avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El elemento actual es 4",
                                *((int*)list_iter_peek_current(iter)) == 4);
    tests_result &= test_assert("El iterador no puede avanzar", !list_iter_forward(iter));
    list_iter_destroy(iter);

    aux = list_pop_head(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 1", *aux == 1);
    free(aux);
    aux = list_pop_head(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 2", *aux == 2);
    free(aux);
    aux = list_pop_head(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 3", *aux == 3);
    free(aux);
    aux = list_pop_head(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 4", *aux == 4);
    free(aux);
    list_destroy(list, free);
    return tests_result;
}

bool test_iter_insert_after_at_tail() {
    bool tests_result = true;
    list_t* list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    int* aux = malloc(sizeof(int));
    *aux = 1;
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, aux));
    aux = malloc(sizeof(int));
    *aux = 2;
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, aux));
    aux = malloc(sizeof(int));
    *aux = 3;
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, aux));
    list_iter_t* iter = list_iter_create_head(list);
    tests_result &= test_assert("El iterador en head fue creado", iter != NULL);
    tests_result &= test_assert("El iterador avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El iterador avanzo", list_iter_forward(iter));
    aux = malloc(sizeof(int));
    *aux = 4;
    tests_result &= test_assert("Se inserto un elemento delante", list_iter_insert_after(iter, aux));
    list_iter_destroy(iter);

    iter = list_iter_create_head(list);
    tests_result &= test_assert("Se creo un nuevo iterador al principio", iter != NULL);
    tests_result &= test_assert("El elemento actual es 1",
                                *((int*)list_iter_peek_current(iter)) == 1);
    tests_result &= test_assert("El iterador avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El elemento actual es 2",
                                *((int*)list_iter_peek_current(iter)) == 2);
    tests_result &= test_assert("El iterador avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El elemento actual es 3",
                                *((int*)list_iter_peek_current(iter)) == 3);
    tests_result &= test_assert("El iterador avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El elemento actual es 4",
                                *((int*)list_iter_peek_current(iter)) == 4);
    tests_result &= test_assert("El iterador no puede avanzar", !list_iter_forward(iter));
    list_iter_destroy(iter);

    aux = list_pop_tail(list);
    tests_result &= test_assert("Se remueve el ultimo elemento y es un 4", *aux == 4);
    free(aux);
    aux = list_pop_tail(list);
    tests_result &= test_assert("Se remueve el ultimo elemento y es un 3", *aux == 3);
    free(aux);
    aux = list_pop_tail(list);
    tests_result &= test_assert("Se remueve el ultimo elemento y es un 2", *aux == 2);
    free(aux);
    aux = list_pop_tail(list);
    tests_result &= test_assert("Se remueve el ultimo elemento y es un 1", *aux == 1);
    free(aux);
    list_destroy(list, free);
    return tests_result;
}


bool test_iter_insert_before_at_end() {
    bool tests_result = true;
    list_t* list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    int* aux = malloc(sizeof(int));
    *aux = 1;
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, aux));
    aux = malloc(sizeof(int));
    *aux = 3;
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, aux));

    list_iter_t* iter = list_iter_create_tail(list);
    tests_result &= test_assert("El iterador en tail fue creado", iter != NULL);
    aux = malloc(sizeof(int));
    *aux = 2;
    tests_result &= test_assert("Se inserto un elemento atras del final", list_iter_insert_before(iter, aux));
    tests_result &= test_assert("El iterador sigue en el final", list_iter_at_last(iter));
    list_iter_destroy(iter);

    iter = list_iter_create_head(list);
    tests_result &= test_assert("Se creo un nuevo iterador al principio", iter != NULL);
    tests_result &= test_assert("El elemento actual es 1",
                                *((int*)list_iter_peek_current(iter)) == 1);
    tests_result &= test_assert("El iterador avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El elemento actual es 2",
                                *((int*)list_iter_peek_current(iter)) == 2);
    tests_result &= test_assert("El iterador avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El elemento actual es 3",
                                *((int*)list_iter_peek_current(iter)) == 3);
    tests_result &= test_assert("El iterador no puede avanzar", !list_iter_forward(iter));
    list_iter_destroy(iter);

    aux = list_pop_head(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 1", *aux == 1);
    free(aux);
    aux = list_pop_head(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 2", *aux == 2);
    free(aux);
    aux = list_pop_head(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 3", *aux == 3);
    free(aux);
    list_destroy(list, free);
    return tests_result;
}

bool test_iter_insert_before_at_end_fails() {
    bool tests_result = true;
    list_t* list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    int* aux = malloc(sizeof(int));
    *aux = 1;
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, aux));
    aux = malloc(sizeof(int));
    *aux = 3;
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, aux));

    list_iter_t* iter = list_iter_create_tail(list);
    tests_result &= test_assert("El iterador en tail fue creado", iter != NULL);
    aux = malloc(sizeof(int));
    *aux = 2;
    set_malloc_status(false);
    tests_result &= test_assert("Fallo insertar un elemento atras del final", !list_iter_insert_before(iter, aux));
    set_malloc_status(true);
    free(aux);
    tests_result &= test_assert("El iterador sigue en el final", list_iter_at_last(iter));
    list_iter_destroy(iter);

    iter = list_iter_create_head(list);
    tests_result &= test_assert("Se creo un nuevo iterador al principio", iter != NULL);
    tests_result &= test_assert("El elemento actual es 1",
                                *((int*)list_iter_peek_current(iter)) == 1);
    tests_result &= test_assert("El iterador avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El elemento actual es 3",
                                *((int*)list_iter_peek_current(iter)) == 3);
    tests_result &= test_assert("El iterador no puede avanzar", !list_iter_forward(iter));
    list_iter_destroy(iter);

    aux = list_pop_head(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 1", *aux == 1);
    free(aux);
    aux = list_pop_head(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 3", *aux == 3);
    free(aux);
    list_destroy(list, free);
    return tests_result;
}

bool test_iter_insert_before_at_middle() {
    bool tests_result = true;
    list_t* list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    int* aux = malloc(sizeof(int));
    *aux = 1;
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, aux));
    aux = malloc(sizeof(int));
    *aux = 3;
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, aux));
    aux = malloc(sizeof(int));
    *aux = 4;
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, aux));
    list_iter_t* iter = list_iter_create_tail(list);
    tests_result &= test_assert("El iterador en head fue creado", iter != NULL);
    tests_result &= test_assert("El iterador retrocedio", list_iter_backward(iter));
    aux = malloc(sizeof(int));
    *aux = 2;
    tests_result &= test_assert("Se inserto un elemento detras", list_iter_insert_before(iter, aux));
    list_iter_destroy(iter);

    iter = list_iter_create_head(list);
    tests_result &= test_assert("Se creo un nuevo iterador al principio", iter != NULL);
    tests_result &= test_assert("El elemento actual es 1",
                                *((int*)list_iter_peek_current(iter)) == 1);
    tests_result &= test_assert("El iterador avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El elemento actual es 2",
                                *((int*)list_iter_peek_current(iter)) == 2);
    tests_result &= test_assert("El iterador avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El elemento actual es 3",
                                *((int*)list_iter_peek_current(iter)) == 3);
    tests_result &= test_assert("El iterador avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El elemento actual es 4",
                                *((int*)list_iter_peek_current(iter)) == 4);
    tests_result &= test_assert("El iterador no puede avanzar", !list_iter_forward(iter));
    list_iter_destroy(iter);

    aux = list_pop_head(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 1", *aux == 1);
    free(aux);
    aux = list_pop_head(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 2", *aux == 2);
    free(aux);
    aux = list_pop_head(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 3", *aux == 3);
    free(aux);
    aux = list_pop_head(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 4", *aux == 4);
    free(aux);
    list_destroy(list, free);
    return tests_result;
}

bool test_iter_insert_before_at_head() {
    bool tests_result = true;
    list_t* list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    int* aux = malloc(sizeof(int));
    *aux = 2;
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, aux));
    aux = malloc(sizeof(int));
    *aux = 3;
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, aux));
    aux = malloc(sizeof(int));
    *aux = 4;
    tests_result &= test_assert("Se inserto un elemento en la lista", list_insert_tail(list, aux));
    list_iter_t* iter = list_iter_create_tail(list);
    tests_result &= test_assert("El iterador en tail fue creado", iter != NULL);
    tests_result &= test_assert("El iterador retrocedio", list_iter_backward(iter));
    tests_result &= test_assert("El iterador retrocedio", list_iter_backward(iter));
    aux = malloc(sizeof(int));
    *aux = 1;
    tests_result &= test_assert("Se inserto un elemento detras de head", list_iter_insert_before(iter, aux));
    list_iter_destroy(iter);

    iter = list_iter_create_head(list);
    tests_result &= test_assert("Se creo un nuevo iterador al principio", iter != NULL);
    tests_result &= test_assert("El elemento actual es 1",
                                *((int*)list_iter_peek_current(iter)) == 1);
    tests_result &= test_assert("El iterador avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El elemento actual es 2",
                                *((int*)list_iter_peek_current(iter)) == 2);
    tests_result &= test_assert("El iterador avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El elemento actual es 3",
                                *((int*)list_iter_peek_current(iter)) == 3);
    tests_result &= test_assert("El iterador avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El elemento actual es 4",
                                *((int*)list_iter_peek_current(iter)) == 4);
    tests_result &= test_assert("El iterador no puede avanzar", !list_iter_forward(iter));
    list_iter_destroy(iter);

    aux = list_pop_head(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 1", *aux == 1);
    free(aux);
    aux = list_pop_head(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 2", *aux == 2);
    free(aux);
    aux = list_pop_head(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 3", *aux == 3);
    free(aux);
    aux = list_pop_head(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 4", *aux == 4);
    free(aux);
    list_destroy(list, free);
    return tests_result;
}

bool test_iter_insert_empty_lists() {
    bool tests_result = true;
    list_t* list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);

    list_iter_t* iter = list_iter_create_head(list);
    tests_result &= test_assert("El iterador en head fue creado", iter != NULL);
    int* aux = malloc(sizeof(int));
    *aux = 1;
    tests_result &= test_assert("Se inserto un 1", list_iter_insert_after(iter, aux));
    tests_result &= test_assert("El iterador está en el primero", list_iter_at_first(iter));
    list_iter_destroy(iter);
    aux = list_pop_head(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 1", *aux == 1);
    free(aux);

    iter = list_iter_create_head(list);
    tests_result &= test_assert("El iterador en head fue creado", iter != NULL);
    aux = malloc(sizeof(int));
    *aux = 2;
    tests_result &= test_assert("Se inserto un 2", list_iter_insert_after(iter, aux));
    tests_result &= test_assert("El iterador está en el primero", list_iter_at_first(iter));
    list_iter_destroy(iter);
    aux = list_pop_tail(list);
    tests_result &= test_assert("Se remueve el ultimo elemento y es un 2", *aux == 2);
    free(aux);

    iter = list_iter_create_tail(list);
    tests_result &= test_assert("El iterador en tail fue creado", iter != NULL);
    aux = malloc(sizeof(int));
    *aux = 3;
    tests_result &= test_assert("Se inserto un 3", list_iter_insert_after(iter, aux));
    tests_result &= test_assert("El iterador está en el ultimo", list_iter_at_last(iter));
    list_iter_destroy(iter);
    aux = list_pop_head(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 3", *aux == 3);
    free(aux);

    iter = list_iter_create_tail(list);
    tests_result &= test_assert("El iterador en tail fue creado", iter != NULL);
    aux = malloc(sizeof(int));
    *aux = 4;
    tests_result &= test_assert("Se inserto un 4", list_iter_insert_after(iter, aux));
    tests_result &= test_assert("El iterador está en el ultimo", list_iter_at_last(iter));
    list_iter_destroy(iter);
    aux = list_pop_tail(list);
    tests_result &= test_assert("Se remueve el ultimo elemento y es un 4", *aux == 4);
    free(aux);

    list_destroy(list, free);
    return tests_result;
}

bool test_iter_delete_empty_list() {
    bool tests_result = true;
    list_t *list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);

    list_iter_t* iter = list_iter_create_head(list);
    tests_result &= test_assert("El iterador en head fue creado", iter != NULL);
    tests_result &= test_assert("No hay nada para borrar", !list_iter_delete(iter));
    list_iter_destroy(iter);

    list_destroy(list, free);
    return tests_result;
}

bool test_iter_delete_one_element_list() {
    bool tests_result = true;
    list_t *list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    int* aux = malloc(sizeof(int));
    *aux = 1;
    tests_result &= test_assert("Se inserto un 1 en la lista", list_insert_tail(list, aux));

    list_iter_t* iter = list_iter_create_head(list);
    tests_result &= test_assert("El iterador en head fue creado", iter != NULL);
    aux = list_iter_delete(iter);
    tests_result &= test_assert("Se elimina un 1 de la lista",
                                *aux == 1);
    free(aux);
    list_iter_destroy(iter);

    tests_result &= test_assert("La lista esta vacia", list_is_empty(list));
    tests_result &= test_assert("No hay nada en el principio", !list_peek_head(list));
    tests_result &= test_assert("No hay nada en el final", !list_peek_tail(list));

    list_destroy(list, free);
    return tests_result;
}

bool test_iter_delete_head() {
    bool tests_result = true;
    list_t *list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    int* aux = malloc(sizeof(int));
    *aux = 1;
    tests_result &= test_assert("Se inserto un 1 en la lista", list_insert_tail(list, aux));
    aux = malloc(sizeof(int));
    *aux = 2;
    tests_result &= test_assert("Se inserto un 2 en la lista", list_insert_tail(list, aux));
    aux = malloc(sizeof(int));
    *aux = 3;
    tests_result &= test_assert("Se inserto un 3 en la lista", list_insert_tail(list, aux));
    aux = malloc(sizeof(int));
    *aux = 4;
    tests_result &= test_assert("Se inserto un 4 en la lista", list_insert_tail(list, aux));

    list_iter_t* iter = list_iter_create_head(list);
    tests_result &= test_assert("El iterador en head fue creado", iter != NULL);
    aux = list_iter_delete(iter);
    tests_result &= test_assert("Se elimina un 1 de la lista",
                                *aux == 1);
    free(aux);
    tests_result &= test_assert("El elemento actual es un 2",
                                *((int*) list_iter_peek_current(iter)) == 2);
    list_iter_destroy(iter);

    iter = list_iter_create_head(list);
    tests_result &= test_assert("Se creo un nuevo iterador al principio", iter != NULL);
    tests_result &= test_assert("El elemento actual es 2",
                                *((int*)list_iter_peek_current(iter)) == 2);
    tests_result &= test_assert("El iterador avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El elemento actual es 3",
                                *((int*)list_iter_peek_current(iter)) == 3);
    tests_result &= test_assert("El iterador avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El elemento actual es 4",
                                *((int*)list_iter_peek_current(iter)) == 4);
    tests_result &= test_assert("El iterador no puede avanzar", !list_iter_forward(iter));
    list_iter_destroy(iter);

    aux = list_pop_head(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 2", *aux == 2);
    free(aux);
    aux = list_pop_head(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 3", *aux == 3);
    free(aux);
    aux = list_pop_head(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 4", *aux == 4);
    free(aux);

    list_destroy(list, free);
    return tests_result;
}

bool test_iter_delete_tail() {
    bool tests_result = true;
    list_t *list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    int* aux = malloc(sizeof(int));
    *aux = 1;
    tests_result &= test_assert("Se inserto un 1 en la lista", list_insert_tail(list, aux));
    aux = malloc(sizeof(int));
    *aux = 2;
    tests_result &= test_assert("Se inserto un 2 en la lista", list_insert_tail(list, aux));
    aux = malloc(sizeof(int));
    *aux = 3;
    tests_result &= test_assert("Se inserto un 3 en la lista", list_insert_tail(list, aux));
    aux = malloc(sizeof(int));
    *aux = 4;
    tests_result &= test_assert("Se inserto un 4 en la lista", list_insert_tail(list, aux));

    list_iter_t* iter = list_iter_create_tail(list);
    tests_result &= test_assert("El iterador en tail fue creado", iter != NULL);
    aux = list_iter_delete(iter);
    tests_result &= test_assert("Se elimina un 4 de la lista",
                                *aux == 4);
    tests_result &= test_assert("El elemento actual es un 3",
                                *((int*) list_iter_peek_current(iter)) == 3);
    free(aux);
    list_iter_destroy(iter);

    iter = list_iter_create_head(list);
    tests_result &= test_assert("Se creo un nuevo iterador al principio", iter != NULL);
    tests_result &= test_assert("El elemento actual es 1",
                                *((int*)list_iter_peek_current(iter)) == 1);
    tests_result &= test_assert("El iterador avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El elemento actual es 2",
                                *((int*)list_iter_peek_current(iter)) == 2);
    tests_result &= test_assert("El iterador avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El elemento actual es 3",
                                *((int*)list_iter_peek_current(iter)) == 3);
    tests_result &= test_assert("El iterador no puede avanzar", !list_iter_forward(iter));
    list_iter_destroy(iter);

    aux = list_pop_tail(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 3", *aux == 3);
    free(aux);
    aux = list_pop_tail(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 2", *aux == 2);
    free(aux);
    aux = list_pop_tail(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 1", *aux == 1);
    free(aux);

    list_destroy(list, free);
    return tests_result;
}

bool test_iter_delete_middle() {
    bool tests_result = true;
    list_t *list = list_new();
    tests_result &= test_assert("La lista fue creada", list != NULL);
    int* aux = malloc(sizeof(int));
    *aux = 1;
    tests_result &= test_assert("Se inserto un 1 en la lista", list_insert_tail(list, aux));
    aux = malloc(sizeof(int));
    *aux = 2;
    tests_result &= test_assert("Se inserto un 2 en la lista", list_insert_tail(list, aux));
    aux = malloc(sizeof(int));
    *aux = 3;
    tests_result &= test_assert("Se inserto un 3 en la lista", list_insert_tail(list, aux));
    aux = malloc(sizeof(int));
    *aux = 8;
    tests_result &= test_assert("Se inserto un 8 en la lista", list_insert_tail(list, aux));
    aux = malloc(sizeof(int));
    *aux = 4;
    tests_result &= test_assert("Se inserto un 4 en la lista", list_insert_tail(list, aux));

    list_iter_t* iter = list_iter_create_tail(list);
    tests_result &= test_assert("El iterador en tail fue creado", iter != NULL);
    tests_result &= test_assert("Se retrocede el iterador", list_iter_backward(iter));
    aux = list_iter_delete(iter);
    tests_result &= test_assert("Se elimina un 8 de la lista",
                                *aux == 8);
    tests_result &= test_assert("El elemento actual es un 4",
                                *((int*) list_iter_peek_current(iter)) == 4);
    free(aux);
    list_iter_destroy(iter);

    iter = list_iter_create_head(list);
    tests_result &= test_assert("Se creo un nuevo iterador al principio", iter != NULL);
    tests_result &= test_assert("El elemento actual es 1",
                                *((int*)list_iter_peek_current(iter)) == 1);
    tests_result &= test_assert("El iterador avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El elemento actual es 2",
                                *((int*)list_iter_peek_current(iter)) == 2);
    tests_result &= test_assert("El iterador avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El elemento actual es 3",
                                *((int*)list_iter_peek_current(iter)) == 3);
    tests_result &= test_assert("El iterador avanzo", list_iter_forward(iter));
    tests_result &= test_assert("El elemento actual es 4",
                                *((int*)list_iter_peek_current(iter)) == 4);
    tests_result &= test_assert("El iterador no puede avanzar", !list_iter_forward(iter));
    list_iter_destroy(iter);

    aux = list_pop_tail(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 4", *aux == 4);
    free(aux);
    aux = list_pop_tail(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 3", *aux == 3);
    free(aux);
    aux = list_pop_tail(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 2", *aux == 2);
    free(aux);
    aux = list_pop_tail(list);
    tests_result &= test_assert("Se remueve el primer elemento y es un 1", *aux == 1);
    free(aux);

    list_destroy(list, free);
    return tests_result;
}


int main(void) {
    srand(42);
    int return_code = 0;
    return_code += !test_create_and_destroy_list();
    return_code += !test_create_with_failed_malloc();
    return_code += !test_empty_size_and_length();
    return_code += !test_insert_head_successfully();
    return_code += !test_insert_head_fails();
    return_code += !test_destroy_value();
    return_code += !test_insert_tail_successfully();
    return_code += !test_insert_tail_fails();
    return_code += !test_peek_head();
    return_code += !test_peek_tail();
    return_code += !test_pop_empty_list();
    return_code += !test_simple_pop_head();
    return_code += !test_simple_pop_tail();
    return_code += !test_multiple_peek();
    return_code += !test_multiple_pop();
    return_code += !test_multiple_pop_random_patterns();
    return_code += !test_multiple_random_failed_operations();
    return_code += !test_iter_create_and_destroy();
    return_code += !test_iter_create_with_failed_malloc();
    return_code += !test_iter_empty_list_move_fails();
    return_code += !test_iter_one_element_list_move_fails();
    return_code += !test_iter_simple_move();
    return_code += !test_iter_peek_empty_list();
    return_code += !test_iter_move_and_peek();
    return_code += !test_iter_move_at_start_and_end();
    return_code += !test_iter_full_list_read_only();
    return_code += !test_iter_move_on_random_list();
    return_code += !test_iter_insert_after_at_start();
    return_code += !test_iter_insert_after_at_start_fails();
    return_code += !test_iter_insert_after_at_middle();
    return_code += !test_iter_insert_after_at_tail();
    return_code += !test_iter_insert_before_at_end();
    return_code += !test_iter_insert_before_at_end_fails();
    return_code += !test_iter_insert_before_at_middle();
    return_code += !test_iter_insert_before_at_head();
    return_code += !test_iter_insert_empty_lists();
    return_code += !test_iter_delete_empty_list();
    return_code += !test_iter_delete_one_element_list();
    return_code += !test_iter_delete_head();
    return_code += !test_iter_delete_tail();
    return_code += !test_iter_delete_middle();
    return return_code;
}
#include "tp1.h"
#include <stdlib.h>

/*
 * Determina si un número es primo.
 */
bool is_prime(int x){
    if (x == 0  || x == 1){
        return false;
    }

    for (int i = 2; i < x; i++) {
        if (x % i == 0){
            return false;
        }
    }
    return true;
}

/*
 * Dado el volumen de un deposito D y el volumen de un producto V
 * la función calcula cuantos productos entran en el depósito.
 */
int storage_capacity(float d, float v){
    return (int)(d/v);
}

/*
 * Intercambia dos valores de enteros.
 */
void swap(int *x, int *y){
    int aux = *x;
    *x = *y;
    *y = aux;
    return;
}

/*
 * Devuelve el máximo de un arreglo de enteros.
 */
int array_max(const int *array, int length){
    int max = 0;
    for (int i = 0; i < length; i++) {
        if (array[i] > max){
            max = array[i];
        }
    }
    return max;
}

/*
 * Aplica la función a cada elemento de un arreglo de enteros.
 */
void array_map(int *array, int length, int f(int)){
    if (f){
        for (int i = 0; i < length; i++) {
            array[i] = f(array[i]);
        }
    }
    return;
}

/*
 * Copia un arreglo de enteros en memoria dinámica.
 * Si el arreglo es NULL devuelve NULL.
 */
int *copy_array(const int *array, int length){
    if (!array){
        return NULL;
    }

    int *array_copy = malloc(sizeof(int) * length);
    for (int i = 0; i<length; i++){
        array_copy[i] = array[i];
    }
    return array_copy;
}

/*
 * Hace bubble sort sobre un arreglo de enteros ascendentemente.
 * Si el arreglo es NULL, no hace nada.
 */
void bubble_sort(int *array, int length){
    if (array){
        int ops;
        do {
            ops = 0;
            for (int i = 0; i < length-1; i++) {
                if (array[i] > array[i+1]){
                    swap(&array[i], &array[i+1]);
                    ops++;
                }
            }
        } while (ops > 0);
    }
    return;
}

/*
 * Determina si dos arreglos de enteros son identicamente iguales.
 * En el caso de que alguno sea NULL solo devuelve true si el otro tambien lo es.
 */
bool array_equal(const int *array1, int length1,
                 const int *array2, int length2){
    if (!array1 || !array2){
        if (!array1 && !array2){
            return true;
        }
        return false;
    }

    if (length1 != length2) {
        return false;
    }

    for (int i = 0; i < length1; i++) {
        if (array1[i] != array2[i]){
            return false;
        }
    }
    return true;
}

/*
 * Determina si dos arrays de enteros son análogos a un anagrama para textos (en algun orden particular, son el mismo arreglo).
 * Si alguno es NULL devuelve false.
 */
bool integer_anagrams(const int *array1, int length1,
                      const int *array2, int length2){
    if (!array1 || !array2){
        return false;
    }

    if (length1 != length2) {
        return false;
    }

    int count = 0;

    for (int i = 0; i < length1; i++) {
        for (int j = 0; j < length2; j++) {
            if (array1[i] == array2[j]){
                count++;
                break;
            }
        }
    }
    return count == length1;
}

/*
 * Copia un arreglo de arreglos de enteros en memoria dinámica.
 * Si alguno de ellos en NULL, continua siendo NULL.
 * Si el arreglo de arreglos es NULL, devuelve NULL.
 *
 * array_of_arrays: un arreglo de punteros a arreglos de enteros
 * array_lenghts: un arreglo con los largos de cada arreglo en array_of_arrays
 * array_amount: la cantidad de arreglos
 */
int **copy_array_of_arrays(const int **array_of_arrays, const int *array_lenghts, int array_amount){
    if (!array_of_arrays) {
        return NULL;
    }

    int **array_of_arrays_copy = malloc(sizeof(int *) * array_amount);
    for (int i = 0; i < array_amount; i++) {
        array_of_arrays_copy[i] = copy_array((const int *)array_of_arrays[i], array_lenghts[i]);
    }
    return array_of_arrays_copy;
}

/*
 * Libera toda la memoria asociada a un arreglo de arreglos.
 *
 * array_of_arrays: un arreglo de punteros a arreglos de enteros
 * array_lenghts: un arreglo con los largos de cada arreglo en array_of_arrays
 * array_amount: la cantidad de arreglos
 */
void free_array_of_arrays(int **array_of_arrays, int *array_lenghts, int array_amount){
    for (int i = 0; i < array_amount; ++i) {
        free(array_of_arrays[i]);
    }
    free(array_lenghts);
    free(array_of_arrays);
    return;
}

#include "tp1.h"
#include "testing.h"
#include <stdbool.h>
#include <stdlib.h>

bool test_is_prime() {
    bool tests_result = true;
    tests_result &= test_assert("Prueba el número 1 es primo", !is_prime(1));
    tests_result &= test_assert("Prueba el número 2 es primo", is_prime(2));
    tests_result &= test_assert("Prueba el número 7 es primo", is_prime(7));
    tests_result &= test_assert("Prueba el número 6 no es primo", !is_prime(6));
    tests_result &= test_assert("Prueba el número 9409 no es primo", !is_prime(9409));
    return tests_result;
}

bool test_storage_capacity() {
    bool tests_result = true;
    tests_result &= test_assert("Prueba de capacidad 0", storage_capacity(1.0, 2.0) == 0);
    tests_result &= test_assert("Prueba de capacidad exactamente 1", storage_capacity(1.0, 1.0) == 1);
    tests_result &= test_assert("Prueba de capacidad 2 con sobrante", storage_capacity(2.0, 0.9f) == 2);
    tests_result &= test_assert("Prueba de capacidad 22", storage_capacity(20.0, 0.9f) == 22);
    return tests_result;
}

bool test_swap() {
    bool tests_result = true;
    int x = 4;
    int y = 5;

    swap(&x, &y);

    tests_result &= test_assert("Prueba swap enteros positivos", (x == 5 && y == 4));

    x = -1;
    y = 1;
    swap(&x, &y);
    tests_result &= test_assert("Prueba swap enteros con signo", (x == 1 && y == -1));

    x = 1;
    y = 1;
    swap(&x, &y);
    tests_result &= test_assert("Prueba swap enteros iguales", (x == 1 && y == 1));
    return tests_result;
}

bool test_array_max() {
    bool tests_result = true;
    int array[5];
    int elem = 10;

    for (int i = 0; i < 5; i++) {
        array[i] = i;
    }
    array[3] = 20;
    tests_result &= test_assert("Prueba máximo de arreglo", array_max(array, 5) == 20);

    for (int i = 0; i < 5; i++) {
        array[i] = 10 - i;
    }
    tests_result &= test_assert("Prueba máximo de arreglo al principio", array_max(array, 5) == 10);

    for (int i = 0; i < 5; i++) {
        array[i] = i;
    }
    tests_result &= test_assert("Prueba máximo de arreglo al final", array_max(array, 5) == 4);

    for (int i = 0; i < 5; i++) {
        array[i] = i;
    }
    array[2] = 20;
    array[3] = 20;
    tests_result &= test_assert("Prueba máximo de arreglo dos veces", array_max(array, 5) == 20);

    tests_result &= test_assert("Prueba máximo de arreglo de un elemento", array_max(&elem, 1) == 10);
    return tests_result;
}

int double_int(int a) {
    return a * 2;
}

bool test_array_map() {
    bool tests_result = true;
    bool test_result = true;
    int array[5];

    for (int i = 0; i < 5; i++) {
        array[i] = i;
    }
    array_map(array, 5, double_int);

    for (int i = 0; i < 5; i++) {
        test_result &= array[i] == i * 2;
    }
    tests_result &= test_assert("Prueba map de arreglo duplicando entero", test_result);

    for (int i = 0; i < 5; i++) {
        array[i] = i;
    }
    array_map(array, 5, NULL);
    for (int i = 0; i < 5; i++) {
        test_result &= array[i] == i;
    }
    tests_result &= test_assert("Prueba map de arreglo sin función", test_result);
    return tests_result;
}

bool test_array_copy() {
    bool tests_result = true;
    bool test_result = true;
    int array[5];

    for (int i = 0; i < 5; i++) {
        array[i] = i;
    }
    int *copy = copy_array(array, 5);

    for (int i = 0; i < 5; i++) {
        test_result &= copy[i] == array[i];
        copy[i] = copy[i] * 2;
        test_result &= copy[i] == array[i] * 2;
    }
    tests_result &= test_assert("Prueba copiar arreglo", test_result);
    free(copy);
    tests_result &= test_assert("Prueba copiar arreglo nulo", !copy_array(NULL, 56));
    return tests_result;
}

bool test_array_of_array_copy() {
    bool tests_result = true;
    bool test_result = true;
    // Inicializo memoria dinámica
    int **array_of_arrays = malloc(sizeof(int *) * 5);
    int *array_lengths = malloc(sizeof(int) * 5);
    int array_amount = 5;
    for (int i = 0; i < array_amount; i++) {
        array_of_arrays[i] = malloc(sizeof(int) * i * 2);
        array_lengths[i] = i * 2;
        for (int j = 0; j < array_lengths[i]; j++) {
            array_of_arrays[i][j] = j;
        }
    }

    int **copy = copy_array_of_arrays((const int **) array_of_arrays, array_lengths, array_amount);
    for (int i = 0; i < array_amount; i++) {
        for (int j = 0; j < array_lengths[i]; j++) {
            test_result &= array_of_arrays[i][j] == copy[i][j];
            copy[i][j] = copy[i][j] * 2;
            test_result &= copy[i][j] == array_of_arrays[i][j] * 2;
        }
    }
    tests_result &= test_assert("Prueba copiar arreglo de arreglos", test_result);
    //Limpio memoria de copia
    for (int i = 0; i < array_amount; i++) {
        free(copy[i]);
    }
    free(copy);

    copy = copy_array_of_arrays(NULL, array_lengths, array_amount);
    tests_result &= test_assert("Prueba copiar arreglo de arreglos nulo", !copy);

    test_result = true;
    free(array_of_arrays[2]);
    array_of_arrays[2] = NULL;

    copy = copy_array_of_arrays((const int **) array_of_arrays, array_lengths, array_amount);

    test_result &= copy[2] == NULL;

    for (int i = 0; i < array_amount; i++) {
        for (int j = 0; j < array_lengths[i]; j++) {
            if (array_of_arrays[i]) {
                test_result &= array_of_arrays[i][j] == copy[i][j];
                copy[i][j] = copy[i][j] * 2;
                test_result &= copy[i][j] == array_of_arrays[i][j] * 2;
            }
        }
    }
    tests_result &= test_assert("Prueba copiar arreglo de arreglos que contiene nulo", test_result);

    // Limpio memoria
    for (int i = 0; i < array_amount; i++) {
        free(copy[i]);
    }
    free(copy);
    free(array_lengths);
    for (int i = 0; i < array_amount; i++) {
        if (array_of_arrays[i]) {
            free(array_of_arrays[i]);
        }
    }
    free(array_of_arrays);

    return tests_result;
}

bool test_free_array_of_arrays() {
    /*
     * Prueba para valgrind
     */
    int **array_of_arrays = malloc(sizeof(int *) * 5);
    int *array_lengths = malloc(sizeof(int) * 5);
    int array_amount = 5;
    for (int i = 0; i < array_amount; i++) {
        array_of_arrays[i] = malloc(sizeof(int) * i * 2);
        array_lengths[i] = i * 2;
        for (int j = 0; j < array_lengths[i]; j++) {
            array_of_arrays[i][j] = j;
        }
    }

    free_array_of_arrays(array_of_arrays, array_lengths, array_amount);

    return true;
}

bool test_bubble_sort() {
    bool tests_result = true;
    bool test_result = true;
    int array[100];
    for (int i = 0; i < 100; i++) {
        array[i] = 99 - i;
    }

    bubble_sort(NULL, 30);
    tests_result &= test_assert("Prueba bubble sort sobre arreglo NULL", true);

    bubble_sort(array, 100);

    for (int i = 0; i < 100; i++) {
        test_result &= array[i] == i;
    }

    tests_result &= test_assert("Prueba bubble sort simple", test_result);
    test_result = true;

    for (int i = 0; i < 100; i++) {
        array[i] = -array[i];
    }
    bubble_sort(array, 100);
    for (int i = 0; i < 100; i++) {
        test_result &= array[i] == -(99 - i);
    }
    tests_result &= test_assert("Prueba bubble sort negativos", test_result);

    return tests_result;
}

bool test_array_equal() {
    bool tests_result = true;
    int array1[5];
    int array2[5];
    for (int i = 0; i < 5; i++) {
        array1[i] = i;
        array2[i] = i;
    }

    tests_result &= test_assert("Prueba igualdad de arreglos largo distinto", !array_equal(array1, 2, array2, 3));
    tests_result &= test_assert("Prueba igualdad de arreglos iguales", array_equal(array1, 5, array2, 5));
    tests_result &= test_assert("Prueba igualdad de arreglos ambos nulos", array_equal(NULL, 5, NULL, 5));
    tests_result &= test_assert("Prueba igualdad de arreglos uno nulo", !array_equal(array1, 5, NULL, 5));
    tests_result &= test_assert("Prueba igualdad de arreglos el otro nulo", !array_equal(NULL, 5, array2, 5));
    array1[3] = 7;
    tests_result &= test_assert("Prueba igualdad de arreglos distintos por un elemento",
                                !array_equal(array1, 5, array2, 5));
    return tests_result;
}

bool test_integer_anagrams() {
    bool tests_result = true;
    int array1[10];
    int array2[10];
    for (int i = 0; i < 10; i++) {
        array1[i] = i;
        array2[i] = i;
    }

    tests_result &= test_assert("Prueba anagramas de arreglos largo distinto", !integer_anagrams(array1, 2, array2, 3));
    tests_result &= test_assert("Prueba anagramas de arreglos iguales", integer_anagrams(array1, 10, array2, 10));
    tests_result &= test_assert("Prueba anagramas de arreglos ambos nulos", !integer_anagrams(NULL, 5, NULL, 5));
    tests_result &= test_assert("Prueba anagramas de arreglos uno nulo", !integer_anagrams(array1, 5, NULL, 5));
    tests_result &= test_assert("Prueba anagramas de arreglos el otro nulo", !integer_anagrams(NULL, 5, array2, 5));
    for (int i = 0; i < 10; i++) {
        array2[i] = 9 - i;
    }
    tests_result &= test_assert("Prueba anagramas de arreglos invertidos", integer_anagrams(array1, 10, array2, 10));
    swap(array1 + 2, array1 + 7);
    swap(array2, array2 + 5);
    tests_result &= test_assert("Prueba anagramas con swap", integer_anagrams(array1, 10, array2, 10));
    array2[4] = 1;
    tests_result &= test_assert("Prueba anagramas cuando son distintos por un elemento",
                                !integer_anagrams(array1, 10, array2, 10));
    return tests_result;
}


int main(void) {
    int return_code = 0;
    return_code += !test_is_prime();
    return_code += !test_storage_capacity();
    return_code += !test_swap();
    return_code += !test_array_max();
    return_code += !test_array_map();
    return_code += !test_bubble_sort();
    return_code += !test_array_equal();
    return_code += !test_integer_anagrams();
    return_code += !test_array_copy();
    return_code += !test_array_of_array_copy();
    return_code += !test_free_array_of_arrays();
    return return_code;
}
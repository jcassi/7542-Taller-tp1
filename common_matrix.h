#ifndef SERVER_MATRIX_H_
#define SERVER_MATRIX_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int *elements;
	size_t rows, cols;
} matrix_t;

/*
 *Se crea una matriz de rows x cols. Devuelve 0 si la puede crear,
 *-1 si no tiene memoria suficiente
*/
int matrix_init(matrix_t *self, size_t rows, size_t cols);

/*
 *Destruye la matriz
*/
void matrix_uninit(matrix_t *self);

/*
 *Llena por filas la matriz con los elementos del vector array de 
 *largo length.
*/
void matrix_fill_by_rows(matrix_t *self, int *array, size_t length);

/*
 *Multiplica la matriz por el vector array y almacena el resultado en 
 *result.
*/
void matrix_multiply_by_array(matrix_t *self, int *array, int *result);

#endif

#ifndef SERVER_MATRIX_H_
#define SERVER_MATRIX_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int **elements;
	size_t rows, cols;
} matrix_t;

int matrix_init(matrix_t *, size_t rows, size_t cols);
void matrix_uninit(matrix_t *self);
void matrix_fill_by_rows(matrix_t *self, int *array, size_t length);
void matrix_fill_by_cols(matrix_t *self, int *array, size_t length);
size_t matrix_get_order(matrix_t *self);
void matrix_multiply_by_array(matrix_t *self, int *array, int *result);

#endif

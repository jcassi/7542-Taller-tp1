#include "common_matrix.h"

int matrix_init(matrix_t *self, size_t rows, size_t cols) {
	if ((self->elements = (int **)malloc(rows * sizeof(int*))) == NULL) {
		return -1;
	}
	for (size_t i = 0; i < rows; i++) {
		if ((self->elements[i] = (int *)malloc(cols * sizeof(int))) == NULL) {
			//BORRAR
		}
	}
	self->rows = rows;
	self->cols = cols;
	return 0;
}
void matrix_uninit(matrix_t *self) {
	for (size_t i = 0; i < self->rows; i++) {
		free(self->elements[i]);
	}
	free(self->elements);
}

void matrix_fill_by_rows(matrix_t *self, int *array, size_t length) {
	for (int i = 0; i < self->rows; i++) {
		for (size_t j = 0; j < self->cols; j++) {
			if(i * self->cols + j < length) {
				self->elements[i][j] = array[i * self->cols + j];
			} else {
				self->elements[i][j] = 0;
			}
		}
	}
}

void matrix_fill_by_cols(matrix_t *self, int *array, size_t length) {
	for (size_t i = 0; i < self->cols; i++) {
		for (size_t j = 0; j < self->rows; j++) {
			if(i * self->rows + j < length) {
				self->elements[j][i] = array[i * self->rows + j];
			} else {
				self->elements[j][i] = 0;
			}
		}
	}
}

size_t matrix_get_order(matrix_t *self) {
	return self->rows * self->cols;
}

void matrix_multiply_by_array(matrix_t *self, int *array, int *result) {
	for (int i = 0; i < self->rows; ++i) {
		result[i] = 0;
		for (int j = 0; j < self->cols; ++j) {
			result[i] += self->elements[i][j] * array[j];	
		}
	}
}

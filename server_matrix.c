#include "server_matrix.h"

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

void matrix_multiply(matrix_t *self, matrix_t *mat, matrix_t *result) {
	for(size_t i = 0; i < self->rows; i++) {
		for (size_t j = 0; j < mat->cols; j++) {
			result->elements[i][j] = 0;
			for (size_t k = 0; k < self->cols; k++) {
				result->elements[i][j] += self->elements[i][k] * mat->elements[k][j];
			}
		}
	}
}

void matrix_mod(matrix_t *self, size_t mod) {
	for (int i = 0; i < self->rows; i++) {
		for (int j = 0; j < self->cols; j++) {
			self->elements[i][j] = self->elements[i][j] % mod;
		}
	}
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

void matrix_to_array_by_columns(matrix_t *self, int mapped_text[]) {
	for (size_t i = 0; i < self->cols; i++) {
		for (size_t j = 0; j < self->rows; j++) {
			mapped_text[i * self->rows + j] = self->elements[j][i];
		}
	}
}

size_t matrix_get_order(matrix_t *self) {
	return self->rows * self->cols;
}

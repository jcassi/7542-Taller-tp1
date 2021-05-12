#include "server_encryptor.h"
#include <math.h>

void encryptor_init(encryptor_t *self, const char *key) {
	size_t length = strlen(key);
	int *mapped_key = (int*)malloc(length * sizeof(int));

	matrix_init(&self->key, (size_t)sqrt(length), (size_t)sqrt(length));
	encryptor_map(self, key, length, mapped_key);
	matrix_fill_by_rows(&self->key, mapped_key, length);
}

void encryptor_uninit(encryptor_t *self) {
	matrix_uninit(&self->key);
}

size_t encryptor_encode(encryptor_t *self,char *str,size_t len,char *result) {
	matrix_t matrix, mat_result;
	char *trimmed = (char*)malloc(len * sizeof(char));
	int *mapped_text = (int*)malloc(len * sizeof(int));
	size_t trimmed_len, cols;

	trimmed_len = encryptor_trim(self, str, len, trimmed);
	encryptor_map(self, trimmed, trimmed_len, mapped_text);
	if (trimmed_len % self->key.cols == 0) {
		cols = trimmed_len / self->key.cols;
	} else {
		cols = trimmed_len / self->key.cols + 1;
	}

	matrix_init(&matrix, self->key.cols, cols);
	matrix_init(&mat_result, self->key.cols, cols);
	matrix_fill_by_cols(&matrix, mapped_text, trimmed_len);
	matrix_multiply(&self->key, &matrix, &mat_result);
	matrix_mod(&mat_result, 26);

	int *encrypted = (int*)malloc(matrix_get_order(&mat_result) * sizeof(int));
	matrix_to_array_by_columns(&mat_result, encrypted);
	encryptor_unmap(self, encrypted, matrix_get_order(&mat_result), result);
	matrix_uninit(&matrix);
	matrix_uninit(&mat_result);
	return mat_result.rows * mat_result.cols;
}
size_t encryptor_trim(encryptor_t *self, char *str, size_t len, char *trimmed) {
 	size_t i, skipped;
 	for (i = 0, skipped = 0; i < len; i++) {
 		if (str[i] >= 'A' && str[i] <= 'Z') {
 			trimmed[i - skipped] = str[i];
 		} else {
 			skipped++;
 		}
 	}
 	return i - skipped;
}

void encryptor_map(encryptor_t *self,const char *str,size_t len,int *result) {
	for (size_t i = 0; i < len; i++) {
		result[i] = str[i] - 'A';
	}
}

void encryptor_unmap(encryptor_t *self, int *str, size_t len, char *result) {
	for (size_t i = 0; i < len; i++) {
		result[i] = str[i] + 'A';
	}
}

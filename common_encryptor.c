#include "common_encryptor.h"
#include <math.h>

void encryptor_init(encryptor_t *self) {
	self->is_key_set = false;
}

int encryptor_set_key(encryptor_t *self, const char *key) {
	size_t length = strlen(key);
	int *mapped_key;

	if ((mapped_key=(int*)malloc(length * sizeof(int))) == NULL) {
		fprintf(stderr, "No memory\n");
		return -1;
	}
	if (matrix_init(&self->key,(size_t)sqrt(length),(size_t)sqrt(length)) != 0) {
		fprintf(stderr, "Error matrix init\n");
		free(mapped_key);
		return -1;
	}
	encryptor_map(self, key, length, mapped_key);
	matrix_fill_by_rows(&self->key, mapped_key, length);
	self->is_key_set = true;
	free(mapped_key);
	return 0;
}

void encryptor_uninit(encryptor_t *self) {
	if (self->is_key_set) {
		matrix_uninit(&self->key);
	}
}

size_t encryptor_encode(encryptor_t *self,char *buf,size_t len,int *encrypted) {
	matrix_t matrix, mat_result;
	char *trimmed = (char*)malloc(len * sizeof(char));
	int *mapped_text = (int*)malloc(len * sizeof(int));
	size_t trimmed_len, cols;

	trimmed_len = encryptor_trim(self, buf, len, trimmed);
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

	matrix_to_array_by_columns(&mat_result, encrypted);

	matrix_uninit(&matrix);
	matrix_uninit(&mat_result);
	free(trimmed);
	free(mapped_text);
	return mat_result.rows * mat_result.cols;
}
size_t encryptor_trim(encryptor_t *self, char *buf, size_t len, char *trimmed) {
 	size_t i, skipped;
 	for (i = 0, skipped = 0; i < len; i++) {
 		if (buf[i] >= 'A' && buf[i] <= 'Z') {
 			trimmed[i - skipped] = buf[i];
 		} else {
 			skipped++;
 		}
 	}
 	return i - skipped;
}

void encryptor_map(encryptor_t *self, const char *buf, size_t len, int *result) {
	for (size_t i = 0; i < len; i++) {
		result[i] = buf[i] - 'A';
	}
}

void encryptor_unmap(encryptor_t *self, int *buf, size_t len, char *result) {
	for (size_t i = 0; i < len; i++) {
		result[i] = buf[i] + 'A';
	}
}

void encryptor_num_to_char(encryptor_t *self,int *numbers,size_t len,char *letters) { 
	for (size_t i = 0; i < len; i++) {
		letters[i] = numbers[i];
	}
}

void encryptor_offset(encryptor_t *self, char *buf, size_t size) {
	for (size_t i = 0; i < size; i++) {
		buf[i] += 'A';
	}
}

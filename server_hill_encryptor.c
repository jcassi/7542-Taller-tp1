#include "hill_encryptor.h"
#include <math.h>

void hill_encryptor_init(hill_encryptor_t *self, char key[]) {
	size_t length = strlen(key);
	int mapped_key[length];


	matrix_init(&self->key, (size_t)sqrt(length), (size_t)sqrt(length));
	hill_encryptor_map_to_numbers(self, key, length, mapped_key);
	matrix_fill_by_rows(&self->key, mapped_key, length);
}

void hill_encryptor_uninit(hill_encryptor_t *self) {
	matrix_uninit(&self->key);
}

size_t hill_encryptor_encrypt(hill_encryptor_t *self, char str[], size_t length, char result[]) {
	matrix_t matrix, mat_result;
	char trimmed[length];
	int mapped_text[length];
	size_t trimmed_length;

	trimmed_length = hill_encryptor_trim(self, str, length, trimmed);
	hill_encryptor_map_to_numbers(self, trimmed, trimmed_length, mapped_text);
	matrix_init(&matrix, 2, (trimmed_length % 2 == 0) ? trimmed_length / 2 : trimmed_length / 2 + 1);
	matrix_init(&mat_result, 2, (trimmed_length % 2 == 0) ? trimmed_length / 2 : trimmed_length / 2 + 1);
	matrix_fill_by_cols(&matrix, mapped_text, trimmed_length);
	matrix_multiply(&self->key, &matrix, &mat_result);
	matrix_mod(&mat_result, 26);

	int encrypted[2 * mat_result.cols];
	matrix_to_array_by_columns(&mat_result, encrypted);
	hill_encryptor_map_to_letters(self, encrypted, 2 * mat_result.cols, result);
	matrix_uninit(&matrix);
	matrix_uninit(&mat_result);
	return trimmed_length;
}
size_t hill_encryptor_trim(hill_encryptor_t *self, char str[], size_t length, char trimmed[]) {
 	size_t i, skipped;
 	for (i = 0, skipped = 0; i < length; i++) {
 		if (str[i] >= 'A' && str[i] <= 'Z') {
 			trimmed[i - skipped] = str[i];
 		} else {
 			skipped++;
 		}
 	}
 	return i - skipped;
}

void hill_encryptor_map_to_numbers(hill_encryptor_t *self,  char str[], size_t length, int result[]) {
	for (size_t i = 0; i < length; i++) {
		result[i] = str[i] - 'A';
	}
}

void hill_encryptor_map_to_letters(hill_encryptor_t *self,  int str[], size_t length, char result[]) {
	for (size_t i = 0; i < length; i++) {
		result[i] = str[i] + 'A';
	}
}

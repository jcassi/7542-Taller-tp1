#include "common_encryptor.h"
#include "common_protocol.h"
#include <math.h>


void encryptor_init(encryptor_t *self) {
	self->is_key_set = false;
}

int encryptor_set_key(encryptor_t *self, const char *key) {
	size_t length = strlen(key);
	int *mapped_key;

	if ((mapped_key=(int*)malloc(length * sizeof(int))) == NULL) {
		return -1;
	}
	if (matrix_init(&self->key,(size_t)sqrt(length),(size_t)sqrt(length)) != 0) {
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
	char *trimmed = (char*)malloc(len * sizeof(char));
	int *mapped_text = (int*)malloc(len * sizeof(int));
	size_t trimmed_len, encrypted_len;

	trimmed_len = encryptor_trim(self, buf, len, trimmed);
	encryptor_map(self, trimmed, trimmed_len, mapped_text);
	encrypted_len = encryptor_get_line_len(self, trimmed_len, self->key.cols);
	encryptor_fill(mapped_text, trimmed_len, encrypted_len);
	encryptor_multiply(self, mapped_text, encrypted, encrypted_len);
	encryptor_mod(self, encrypted, encrypted_len, 26);

	free(trimmed);
	free(mapped_text);
	return encrypted_len;
}

size_t encryptor_trim(encryptor_t *self, char *buf,
			size_t len, char *trimmed) {
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

void encryptor_map(encryptor_t *self, const char *buf,
			size_t len, int *result) {
	for (size_t i = 0; i < len; i++) {
		result[i] = buf[i] - 'A';
	}
}

void encryptor_num_to_char(encryptor_t *self,
			int *numbers, size_t len, char *letters) { 
	for (size_t i = 0; i < len; i++) {
		letters[i] = numbers[i];
	}
}

void encryptor_offset(encryptor_t *self, char *buf, size_t size) {
	for (size_t i = 0; i < size; i++) {
		buf[i] += 'A';
	}
}

void encryptor_fill(int *mapped_text, size_t len, size_t encrypted_len) {
	if (len != encrypted_len) {
		for (size_t i = len; i < encrypted_len; i++) {
			mapped_text[i] = 0;
		}
	}
}

void encryptor_mod(encryptor_t *self, int *encrypted, size_t size, int mod) {
	for (int i = 0; i < size; ++i) {
		encrypted[i] %= mod;
	}
}

size_t encryptor_get_line_len(encryptor_t *self, size_t trimmed_len, size_t key_cols) {
	if (trimmed_len % key_cols == 0) {
		return key_cols * (trimmed_len / key_cols);
	} else {
		return key_cols * (trimmed_len / key_cols + 1);
	}
}

void encryptor_multiply(encryptor_t *self, int *mapped_text, int *encrypted, size_t len) {
	for (int i = 0; i < len; i += self->key.cols) {
		matrix_multiply_by_array(&self->key, mapped_text + i, encrypted + i);
	}
}


#ifndef SERVER_HILL_ENCRYPTOR_H_
#define SERVER_HILL_ENCRYPTOR_H_

#include <math.h>
#include "common_matrix.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
	matrix_t key;
	bool is_key_set;
} encryptor_t;

void encryptor_init(encryptor_t *self);
int encryptor_set_key(encryptor_t *self, const char *key);
void encryptor_uninit(encryptor_t *self);
size_t encryptor_encode(encryptor_t *self, char *str, size_t len, int *result);
size_t encryptor_trim(encryptor_t *self, char *str, size_t len, char *trimmed);
void encryptor_map(encryptor_t *self, const char *str, size_t len, int *result);
void encryptor_unmap(encryptor_t *self, int *str, size_t len, char *result);
void encryptor_num_to_char(encryptor_t *self,int *numbers,size_t len,char *letters);
void encryptor_offset(encryptor_t *self, char *buf, size_t size);

#endif

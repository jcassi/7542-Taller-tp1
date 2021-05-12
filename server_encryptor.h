#ifndef SERVER_HILL_ENCRYPTOR_H_
#define SERVER_HILL_ENCRYPTOR_H_

#include <math.h>
#include "server_matrix.h"
#include <stdio.h>
#include <string.h>

typedef struct {
	matrix_t key;
} encryptor_t;

void encryptor_init(encryptor_t *self, const char *key);
void encryptor_uninit(encryptor_t *self);
size_t encryptor_encode(encryptor_t *self, char *str, size_t len, char *result);
size_t encryptor_trim(encryptor_t *self, char *str, size_t len, char *trimmed);
void encryptor_map(encryptor_t *self, const char *str, size_t len, int *result);
void encryptor_unmap(encryptor_t *self, int *str, size_t len, char *result);


#endif

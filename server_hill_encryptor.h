#ifndef HILL_ENCRYPTOR_H_
#define HILL_ENCRYPTOR_H_

#include <math.h>
#include "matrix.h"
#include <stdio.h>

typedef struct {
	matrix_t key;

} hill_encryptor_t;

void hill_encryptor_init(hill_encryptor_t *self, char str[], size_t length);
void hill_encryptor_uninit(hill_encryptor_t *self);
size_t hill_encryptor_encrypt(hill_encryptor_t *self, char str[], size_t length, char result[]);
size_t hill_encryptor_trim(hill_encryptor_t *self, char str[], size_t length, char trimmed[]);
void hill_encryptor_map_to_numbers(hill_encryptor_t *self,  char str[], size_t length, int result[]);
void hill_encryptor_map_to_letters(hill_encryptor_t *self,  int str[], size_t length, char result[]);


#endif
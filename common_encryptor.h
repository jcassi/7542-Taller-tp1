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

/*
 *Función para inicializar el cifrador
*/
void encryptor_init(encryptor_t *self);

/*
 *Función para setear la clave del cifrador. Recibe la clave.
 *Devuelve -1 si no tiene memoria suficiente para almacenar
 *la clave, 0 si sí puede
*/
int encryptor_set_key(encryptor_t *self, const char *key);

/*
 *Función para destruir el cifrador.
*/
void encryptor_uninit(encryptor_t *self);


/*
 *Función para cifrar el mensaje str de largo len. Almacena el resultado en
 *result.
 *Devuelve el largo de la línea encriptada.
*/
size_t encryptor_encode(encryptor_t *self, char *str, size_t len,
						int *result);

/*
 *Función para filtrar de la línea str de largo len los caracteres que no
 *estén en el rango A-Z. Almacena el resultado en trimmed y devuelve su largo.
*/
size_t encryptor_filter(encryptor_t *self, char *str, size_t len,
						char *trimmed);

/*
 *Función para mapear los caracteres de str de largo len a números.
 *A->0, B->1, ..., Z->25
 *Almacena el resultado del mapeo en result
*/
void encryptor_map(encryptor_t *self, const char *str, size_t len,
					int *result);

/*
 *Función para convertir un vector de enteros numbers de largo len en
 *un string del mismo largo con esos valores como caracteres.
*/
void encryptor_num_to_char(encryptor_t *self,
			int *numbers, size_t len, char *letters);

/*
 *Función que toma los caracteres del string buf (de largo size) y
 *les suma un offset de forma tal que 0->A, 1->B, ..., 25->Z.
*/
void encryptor_offset(encryptor_t *self, char *buf, size_t size);

/*
 *Si el largo len del texto mapeado (mapped_text) es menor al necesario según
 *el largo de la clave, se rellenan los valores restantes con 0.
*/
void encryptor_fill(int *mapped_text, size_t len, size_t matrix_order);

/*
 *Se realiza la operación módulo mod a cada elemento del vector
 *encrypted_line, de largo size.
*/
void encryptor_mod(encryptor_t *self, int *encrypted_line,
					size_t size, int mod);

/*
 *Se obtiene el largo de debe tener la línea encriptada según el largo
 *de la clave
*/
size_t encryptor_get_line_len(encryptor_t *self, size_t trimmed_len,
								size_t key_cols);

/*
 *Se multiplica la matriz de la clave con el vector del texto mapade
 *(mapped_text) de largo len y se almacena el resultado en el vector
 *encrypted.
*/
void encryptor_multiply(encryptor_t *self, int *mapped_text,
						int *encrypted, size_t len);


#endif

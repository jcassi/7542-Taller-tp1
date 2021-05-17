#ifndef CLIENT_H_
#define CLIENT_H_

#include "common_socket.h"
#include "common_encryptor.h"
#include "common_protocol.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct client {
	socket_t skt;
	FILE *fp;
	bool is_stdin;
	encryptor_t encryptor;
	protocol_t protocol;
}client_t;

/*
 *Función para inicializar cliente con sus componentes. Abre el archivo 
 *del cual va a leer.
 *Devuelve 0 en caso exitoso, -1 en caso contrario.
*/
int client_init(client_t *self, const char *file_name);

/*
 *Cierra el socket y el archivo.
 *Devuelve 0 en caso exitoso, -1 en caso contrario.
*/
void client_uninit(client_t *self);

/*
 *Lee línea por línea el archivo, lo envía al servidor, recibe su
 *respuesta y lo imprime por stdout luego de aplicarle el offset.
 *Devuelve 0 si puede enviar y recibir exitosamente todas las líneas,
 *-1 en caso contrario.
*/
int client_iterate(client_t *self);

/*
 *Conecta el cliente al servidor informado por host y service.
 *Devuelve 0 si logra conectarse, -1 en caso contrario.
*/
int client_connect(client_t *self, const char *host, const char *service);

#endif

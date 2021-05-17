#ifndef SERVER_H_
#define SERVER_H_

#include "common_socket.h"
#include "common_encryptor.h"
#include "common_protocol.h"
#include <stdio.h>
#include <string.h>


typedef struct server {
	socket_t listener;
	socket_t peer;
	encryptor_t encryptor;
}server_t;

/*
 *Inicializa el server. Deja el socket listo para recibir datos con
 *el service. Recibe la clave key para el cifrador.
 *Devuelve 0 si se inicializa todo correctamente, -1 en caso
 *contrario.
*/
int server_init(server_t *self, const char *service, const char *key);

/*
 *Cierra el socket destruye el cifrador.
*/
void server_uninit(server_t *self);

/*
 *Recibe una línea del cliente y se la devuelve encriptada usando
 *cifrado Hill. Repite este proceso hasta que al cliente ya no
 *envía más nada.
 *Devuelve 0 si realiza este proceso correctamente.
*/
int server_iterate(server_t *self);

#endif

#ifndef COMMON_SOCKET_H
#define COMMON_SOCKET_H

#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

typedef struct {
    int fd;
} socket_t;

/*
 *Inicializa el socket con fd = -1.
*/
void socket_init(socket_t *self);

/*
 *Cierra el socket
*/
void socket_uninit(socket_t *self);

/*
 *Realiza el bind and listen del socket con host y service.
 *Devuelve 0 si logra hacerlo, -1 si falla.
*/
int socket_bind_and_listen(socket_t *self,
                            const char *host,
                            const char *service);

/*
 *Acepta la comunicación e inicializa peer con el fd para hacerlo.
 *Devuelve 0 si logra aceptar la comunicación, -1 si no.
*/
int socket_accept(socket_t *listener, socket_t *peer);

/*
 *Función para conectar este socket con el host y service provisto por
 *parámetros. Si se puede conectar deja el socket listo para la enviar o
 *recibir y devuelve 0. Si no, devuelve -1.
*/
int socket_connect(socket_t *self, const char *host, const char *service);

/*
 *Envía el string buffer de larglo length por el socket.
 *Devuelve la cantidad de bytes que pudo enviar o -1 ocurre un error.
*/
ssize_t socket_send(socket_t *self, const char *buffer, size_t length);

/*
 *Recibe una línea de largo length por el socket y almacena en buffer.
 *Devuelve la cantidad de bytes que pudo recibir o -1 ocurre un error.
*/
ssize_t socket_receive(socket_t *self, char *buffer, size_t length);

#endif

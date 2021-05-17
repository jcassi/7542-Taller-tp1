#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "common_socket.h"

typedef struct {
	socket_t *skt;
}protocol_t;

/*
 *Inicializa el protocolo con el socket recibido por parámetro.
 */
void protocol_init(protocol_t *self, socket_t *skt);

/*
 *Destruye el protocolo. No cierra el socket.
 */
void protocol_uninit(protocol_t *self);

/*
 *Función que envía por el socket 2 bytes con el largo len de la línea
 *que va a enviar a continuación.
 *Devuelve 0 si logra enviar correctamente el largo, -1 en caso
 *contrario.
 */
int protocol_send_line_length(protocol_t *self, size_t len);

/*
 *Envía la línea de largo len que hay en buffer por el socket que tiene
 *el protocolo.
 *Devuelve 0 si logra enviar correctamente la línea, -1 caso contrario.
 */
int protocol_send_line(protocol_t *self, char *buffer, size_t len);

/*
 *Recibe una línea por el socket y la almacena en *buffer (previo debe 
 *haber pedido memoria). Guarda el largo de la línea en el puntero len.
 *Devuelve 0 si recibe bien la línea y tiene espacio para almacenarla,
 *-1 en caso contrario.
 */
int protocol_receive_line(protocol_t *self, char **buffer, size_t *len);

/*
 *Recibe los dos bytes con el largo de la línea a recibir a continuación
 *Guarda este largo en el puntero len.
 *Devuelve 0 si puede recibir bien los dos bytes, -1 en caso contrario.
 */
int protocol_receive_line_length(protocol_t *self, size_t *len);

#endif

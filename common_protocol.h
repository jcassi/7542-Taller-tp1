#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <stddef.h>
#include "common_socket.h"

typedef struct {
	socket_t *skt;
}protocol_t;

void protocol_init(protocol_t *self, socket_t *skt);
void protocol_uninit(protocol_t *self);
int protocol_send_line_length(protocol_t *self, size_t len);
int protocol_send_line(protocol_t *self, char *buffer, size_t len);
int protocol_receive_line(protocol_t *self, char *buffer, size_t *len);
int protocol_receive_line_length(protocol_t *self, size_t *len);

#endif

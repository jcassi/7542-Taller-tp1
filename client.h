#ifndef CLIENT_H_
#define CLIENT_H_

#include "common_socket.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct client {
	socket_t skt;
	FILE *fp;
	bool is_stdin;
}client_t;

void client_init(client_t *self, const char *file_name);
void client_uninit(client_t *self);
void client_iterate(client_t *self);
void client_connect(client_t *self, const char *host, const char *service);

#endif

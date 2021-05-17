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
	//protocol_t protocol;
}server_t;


int server_init(server_t *self, const char *service, const char *key);
void server_uninit(server_t *self);
int server_iterate(server_t *self);

#endif

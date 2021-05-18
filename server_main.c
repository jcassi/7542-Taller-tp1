#include "common_socket.h"
#include "server.h"

#define ARGS_COUNT 3

int main(int argc, char const *argv[])
{
	server_t server;

	if (argc != ARGS_COUNT) {
		return -1;
	}
	if (server_init(&server, argv[1], argv[2]) != 0) {
		return -1;
	}
	if (server_iterate(&server) != 0) {
		server_uninit(&server);
		return -1;
	}
	server_uninit(&server);
	return 0;
}

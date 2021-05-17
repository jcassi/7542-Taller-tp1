#include "common_socket.h"
#include "server.h"


int main(int argc, char const *argv[])
{
	//validar argvs
	server_t server;

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

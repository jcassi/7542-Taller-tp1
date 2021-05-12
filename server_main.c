#include "common_socket.h"
#include "server.h"


int main(int argc, char const *argv[])
{
	//validar argvs
	server_t server;

	server_init(&server, argv[1], argv[2]);
	server_iterate(&server);
	server_uninit(&server);
	return 0;
}

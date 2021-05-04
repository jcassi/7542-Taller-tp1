#include "socket.h"
#include "server.h"



int int main(int argc, char const *argv[])
{
	//validar argvs
	server_init(&serv, argv[1], argv[2]);
	server_iterate(&serv);
	server_uninit(&serv);
	return 0;
}
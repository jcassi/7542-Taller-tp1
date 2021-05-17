#include "client.h"

int main(int argc, char const *argv[]) {
	client_t client;

	//validar argvs
	if (client_init(&client, argv[3]) != 0) {
		return -1;
	}
	if (client_connect(&client, argv[1], argv[2]) != 0) {
		client_uninit(&client);
		return -1;
	}
	if (client_iterate(&client) != 0) {
		client_uninit(&client);
		return -1;
	}
	client_uninit(&client);
	return 0;
}

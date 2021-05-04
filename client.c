#include "client.h"

void client_init(client_t *self, const char *file_name) {
	socket_init(&self->skt);
	if (strlen(file_name) == 1 && file_name[0] == '-') {
		self->fp = stdin;
	} else {
		self->fp = fopen(file_name, "rt");
	}
}

void client_uninit(client_t *self) {
	socket_uninit(&self->skt);
	fclose(self->fp);
}

void client_iterate(client_t *self) {
	char *buffer = NULL;
	char line_length[2]; 
	size_t length = 1;
	ssize_t chars_read = 1;


	while(chars_read > 0) {
		buffer = (char *)malloc(length * sizeof(char));
		chars_read = getline(&buffer, &length, self->fp);
		if (chars_read < 0) {
			free(buffer);
			break;
		}
		line_length[0] = '0';//cambiar
		line_length[1] = chars_read; //cambiar
		socket_send(&self->skt, line_length, 2);
		socket_send(&self->skt, buffer, chars_read);
		socket_receive(&self->skt, buffer,  chars_read);
		//imprimir por stdout
		free(buffer);
		
	}
}

void client_connect(client_t *self, const char *host, const char *service) {
	socket_connect(&self->skt, host, service);
}
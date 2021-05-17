#include "client.h"

int client_init(client_t *self, const char *file_name) {
	if (strlen(file_name) == 1 && file_name[0] == '-') {
		self->fp = stdin;
		self->is_stdin = true;
	} else {
		if ((self->fp = fopen(file_name, "rt")) == NULL) {
			return -1;
		}
		self->is_stdin = false;
	}
	socket_init(&self->skt);
	encryptor_init(&self->encryptor);
	return 0;
}

void client_uninit(client_t *self) {
	socket_uninit(&self->skt);
	if (!self->is_stdin) {
		fclose(self->fp);
	}
}

int client_iterate(client_t *self) {
	char *buffer = NULL;
	size_t length = 0, chars_received;
	ssize_t chars_read = 1;

	while(chars_read > 0) {
		chars_read = getline(&buffer, &length, self->fp);
		if (chars_read < 0) {
			free(buffer);
			return 0;
		}
		if (client_send_line(self, buffer, chars_read) != 0) {
			free(buffer);
			return -1;
		}
		if (client_receive_line(self, buffer, &chars_received) != 0) {
			free(buffer);
			return -1;
		}
		encryptor_offset(&self->encryptor, buffer, chars_received);
		fprintf(stdout, "%.*s\n", (int)chars_received, buffer);
	}
	free(buffer);
	return 0;
}

int client_connect(client_t *self, const char *host, const char *service) {
	if (socket_connect(&self->skt, host, service) != 0) {
		return -1;
	}
	return 0;
}

int client_send_line_length(client_t *self, size_t len) {
	char line_length[2];
	line_length[0] = len / 256;
	line_length[1] = len % 256;
	if (socket_send(&self->skt, line_length, 2) == -1) {
		return -1;
	}
	return 0;
}

int client_send_line(client_t *self, char *buffer, size_t len) {
	if (len > 256 * 256) {
		return -1;
	}
	if (client_send_line_length(self, len) != 0) {
		return -1;
	}
	if (socket_send(&self->skt, buffer, len) != len) {
		free(buffer);
		return -1;
	}
	return 0;
}

int client_receive_line(client_t *self, char *buffer, size_t *len) {
	if (client_receive_line_length(self, len) != 0) {
		return -1;
	}
	size_t chars_received;
	if ((chars_received = socket_receive(&self->skt, buffer, *len)) != *len) {
		return -1;
	}
	return 0;
}

int client_receive_line_length(client_t *self, size_t *len) {
	char line_length[2];

	if (socket_receive(&self->skt, line_length, 2) == -1) {
		return -1;
	}
	*len = line_length[0] * 256 + line_length[1];
	return 0;
}

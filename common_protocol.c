#include "common_protocol.h"

void protocol_init(protocol_t *self, socket_t *skt) {
	self->skt = skt;
}

void protocol_uninit(protocol_t *self){
	self->skt = NULL;
}

int protocol_send_line_length(protocol_t *self, size_t len) {
	char line_length[2];
	line_length[0] = len / 256;
	line_length[1] = len % 256;
	if (socket_send(self->skt, line_length, 2) == -1) {
		return -1;
	}
	return 0;
}

int protocol_send_line(protocol_t *self, char *buffer, size_t len) {
	if (len > 256 * 256) {
		return -1;
	}
	if (protocol_send_line_length(self, len) != 0) {
		return -1;
	}
	if (socket_send(self->skt, buffer, len) != len) {
		return -1;
	}
	return 0;
}

int protocol_receive_line(protocol_t *self, char **buffer, size_t *len) {
	if (protocol_receive_line_length(self, len) != 0) {
		return -1;
	}
	*buffer = (char*)malloc(*len * sizeof(char));
	size_t chars_received = socket_receive(self->skt, *buffer, *len);
	if (chars_received != *len) {
		free(buffer);
		return -1;
	}
	return 0;
}

int protocol_receive_line_length(protocol_t *self, size_t *len) {
	char line_length[2];

	if (socket_receive(self->skt, line_length, 2) == -1) {
		return -1;
	}
	*len = line_length[0] * 256 + line_length[1];
	return 0;
}

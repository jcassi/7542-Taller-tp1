#include "server.h"

int server_init(server_t *self, const char *service, const char *key) {
	socket_init(&self->listener);
	encryptor_init(&self->encryptor);
	if (encryptor_set_key(&self->encryptor, key) != 0) {
		server_uninit(self);
		return -1;
	}
	if (socket_bind_and_listen(&self->listener, "localhost", service) != 0) {
		server_uninit(self);
		return -1;
	}
	if (socket_accept(&self->listener, &self->peer) != 0) {
		server_uninit(self);
		return -1;
	}
	return 0;
}
void server_uninit(server_t *self) {
	socket_uninit(&self->listener);
	socket_uninit(&self->peer);
	encryptor_uninit(&self->encryptor);
}

int server_iterate(server_t *self) {
	bool socket_still_open = true;
	char *line_buffer;
	protocol_t protocol;

	protocol_init(&protocol, &self->peer);

	while (socket_still_open) {
		size_t len;
		if (protocol_receive_line(&protocol, &line_buffer, &len) != 0) {
			return -1;
		}
		if (len == 0) {
			free(line_buffer);
			socket_still_open = false;
		} else {
			int *encrypted_line = (int*)malloc((len + 3) * sizeof(int));
			len = encryptor_encode(&self->encryptor, line_buffer,
						len, encrypted_line);
			char *encrypted_as_chars = (char*)malloc(len * sizeof(char));
			encryptor_num_to_char(&self->encryptor, encrypted_line,
						len, encrypted_as_chars);
			if (protocol_send_line(&protocol, encrypted_as_chars, len) != 0) {
				return -1;
			}
			free(line_buffer);
			free(encrypted_line);
			free(encrypted_as_chars);
		}
	}

	protocol_uninit(&protocol);
	return 0;
}

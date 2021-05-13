#include "server.h"

void server_init(server_t *self, const char *service, const char *key) {
	socket_init(&self->listener);
	encryptor_init(&self->encryptor);
	encryptor_set_key(&self->encryptor, key);
	socket_bind_and_listen(&self->listener, "localhost", service);
	socket_accept(&self->listener, &(self->peer));
}
void server_uninit(server_t *self) {
	socket_uninit(&(self->listener));
	encryptor_uninit(&self->encryptor);
}

void server_iterate(server_t *self) {
	bool socket_still_open = true;
	char length_buffer[2], *line_buffer;

	while (socket_still_open) {
		ssize_t s;

		memset(length_buffer, 0, 2);
		s = socket_receive(&self->peer, length_buffer, 2);
		if (s == 0) {
			socket_still_open = false;
		} else {
			int size = length_buffer[0]*256 + length_buffer[1];
			line_buffer = (char *)malloc(size * sizeof(char)); 
			s = socket_receive(&self->peer, line_buffer, size);
			if (s == 0) {
				socket_still_open = false;
			}
			int *encrypted_line = (int*)malloc((size + 10) * sizeof(int));
			size = encryptor_encode(&self->encryptor,line_buffer,s,encrypted_line);
			char *encrypted_as_chars = (char*)malloc(size * sizeof(char));
			encryptor_num_to_char(&self->encryptor,encrypted_line,size,encrypted_as_chars);
			length_buffer[0] = size / 256;
			length_buffer[1] = size % 256;
			socket_send(&self->peer, length_buffer, 2);
			size = socket_send(&self->peer, encrypted_as_chars, size);

			free(line_buffer);
			free(encrypted_line);
			free(encrypted_as_chars);
		}
	}
}

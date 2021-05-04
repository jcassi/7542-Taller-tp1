#include "socket.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>



void socket_init(socket_t *self) {
	self->fd = -1;
}
void socket_uninit(socket_t *self) {

}

int socket_bind_and_listen(socket_t *self,
                            const char *host,
                            const char *service) {
  struct addrinfo hints;
	struct addrinfo *result, *rp; 
	int status;
	int fd;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family   = AF_INET;/*IPv4*/
	hints.ai_socktype = SOCK_STREAM;/*TCP*/
	hints.ai_flags    = AI_PASSIVE;

	status = getaddrinfo(host/*ANY*/, service, &hints, &result);

  if (status != 0) {
        return -1;
    }

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (fd == -1) {
            continue;
        }
        if (bind(fd, rp->ai_addr, rp->ai_addrlen) == 0) {
        	self->fd = fd;
            break;                  
        }
        close(fd);
    }

    if (rp == NULL) {               
        return -1;
    }

    freeaddrinfo(result);

    if (listen(fd, 2) == -1) {
    	close(fd);
    	return -1;
    }
    return 0;
}

int socket_accept(socket_t *listener, socket_t *peer) {
	int fd;

	fd = accept(listener->fd, NULL, NULL);
	if (fd == -1) {
		return -1;
	} else {
		peer->fd = fd;
	}
	return 0;
}

int socket_connect(socket_t *self, const char *host, const char *service) {
	struct addrinfo hints;
	struct addrinfo *result, *rp; 
	int status;
	int fd, s;

	memset(&hints, 0, sizeof(struct addrinfo));
           hints.ai_family = AF_INET;    
           hints.ai_socktype = SOCK_STREAM; 
           hints.ai_flags = 0;

           s = getaddrinfo(host, service, &hints, &result);
           if (s != 0) {
               return -1;
           }

           for (rp = result; rp != NULL; rp = rp->ai_next) {
               fd = socket(rp->ai_family, rp->ai_socktype,
                            rp->ai_protocol);
               if (fd == -1){
                   continue;
              }
               if (connect(fd, rp->ai_addr, rp->ai_addrlen) != -1) {
                   break;                  
                }
               close(fd);
           }

           freeaddrinfo(result);           

           if (rp == NULL) {               
               return -1;
           }
    self->fd = fd;
    return 0;
}

ssize_t socket_send(socket_t *self, const char *buffer, size_t length) {
	int bytes_sent = 0;
	bool skt_still_open = true;
	int s;

 	while ((length > bytes_sent) && skt_still_open) {
 		s = send(self->fd, &buffer[bytes_sent], length - bytes_sent, MSG_NOSIGNAL);
 		if (s == -1) { 
 			skt_still_open = false;
 			return -1;
 		} else if (s == 0) { 
 			skt_still_open = false;
 		} else {
 			bytes_sent += s;
 		}
 	}
 	return bytes_sent;
}



ssize_t socket_receive(socket_t *self, char *buffer, size_t length) {
	int bytes_recv = 0, s;
	bool skt_still_open = true;

	while ((length > bytes_recv) && skt_still_open) {
		s = recv(self->fd, &buffer[bytes_recv], length - bytes_recv, 0);
		if (s == -1) { 
			skt_still_open = false;
			return -1;
		}
		else if (s == 0) { 
			skt_still_open = false;
		}
		else {
			bytes_recv += s;
		}
	}
	return bytes_recv;
}

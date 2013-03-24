#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <cstring>
#include <string>
#include "TcpSocket.h"

/**
 * Creates a TCP socket
 * @param family - socket family type, optional. Defaults to AF_INET.
 * @throws system call errno on socket creation
 */
TcpSocket::TcpSocket(int family)
	throw (int) : family(family) {

	sock_fd = socket(family, SOCK_STREAM, 0);

	if(sock_fd < 0) {
		throw errno;
	}
}

/**
 * Send data to other end of socket
 * @param data - data to send
 * @param size - number of bytes to send
 * @return number of bytes sent
 */
int TcpSocket::send(void *data, int size) {

	return write(sock_fd, data, size);
}

/**
 * Receive data from other end of socket
 * @param data - buffer in which to store data
 * @param size - max number of bytes to store
 * @return number of bytes sent
 */
int TcpSocket::receive(void *data, int size) {

	return read(sock_fd, data, size);
}

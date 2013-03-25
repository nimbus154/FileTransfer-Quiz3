#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <cstring> // memset
#include "TcpServer.h"

/**
 * Creates a TCP server
 * @param family - socket family type, optional. Defaults to AF_INET.
 * @throws system call errno on socket creation
 */

TcpServer::TcpServer(int family)
	throw (int) : TcpSocket(family) { }

/**
 * Begin listening for connections
 * @param port - port on which to listen
 * @param ip - (optional) IP address to listen on, default to any
 * @returns true if successfully listening
 */
bool TcpServer::listen(unsigned short port, long address) {

	struct sockaddr_in server_addr;

	// clear address structure
	memset(&server_addr, 0, sizeof(server_addr));
	
	server_addr.sin_family = family;
	server_addr.sin_port = htons(port);

	server_addr.sin_addr.s_addr = htonl(address);

	// TODO check for value >= 0
	bind(sock_fd, (sockaddr *) &server_addr, sizeof(server_addr));

	::listen(sock_fd, 100); // TODO should be >= 0, 100 pending clients
}

/**
 * Accept a connection request
 * @returns true if connection was established
 */
bool TcpServer::accept() {

	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);

	return ::accept(sock_fd, (sockaddr *)&client_addr, &client_len) >= 0;
}

/**
 * Send data to client
 * @param data - data to send
 * @param size - number of bytes to send
 * @return number of bytes sent
 */
int TcpServer::send(void *data, int size) {

	return write(client_fd, data, size);
}

/**
 * Receive data from client
 * @param data - buffer in which to store data
 * @param size - max number of bytes to store
 * @return number of bytes sent
 */
int TcpServer::receive(void *data, int size) {

	return read(client_fd, data, size);
}

/**
 * Close current client connection
 * @throws errno - error number corresponding to reason for failure
 */
void TcpServer::close() throw (int){

	if(::close(client_fd) < 0) {
		throw errno;
	}
}

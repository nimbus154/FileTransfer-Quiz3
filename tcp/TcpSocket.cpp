#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <cstring>
#include <string>
#include "TcpSocket.h"

/**
 * Creates a TCP socket
 * @param ip - IP address of target machine
 * @param port - port on which to connect 
 * @param domain - socket family type, optional. Defaults to AF_INET.
 * @throws system call errno on socket creation
 */
TcpSocket::TcpSocket()//int domain)
	throw (int) {

	int domain = AF_INET;
	this->domain = domain;
	sock_fd = socket(domain, SOCK_STREAM, 0);

	if(sock_fd < 0) {
		throw errno;
	}
}


bool TcpSocket::connect(char *ip, unsigned short port) 
	throw (const char *){
	
	// specify server IP and port
	struct sockaddr_in server_addr;

	// clear address structure
	memset(&server_addr, 0, sizeof(server_addr));
	
	server_addr.sin_family = this->domain;
	server_addr.sin_port = htons(port);

	// set IP
	int inet_result = inet_pton(AF_INET, ip, &server_addr.sin_addr);

	if(inet_result == 0) {
		throw "Invalid address format";
	}
	else if(inet_result < 0) {
		throw "Error converting IP to binary";
	}

	return ::connect(sock_fd, (sockaddr*)&server_addr, sizeof(sockaddr)) >= 0;
}


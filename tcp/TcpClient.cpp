#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <cstring>
#include <string>
#include "TcpClient.h"

/**
 * Creates a TCP Client
 * @param family - socket family type, optional. Defaults to AF_INET.
 * @throws system call errno on socket creation
 */
TcpClient::TcpClient(int family)
	throw (int) : TcpSocket(family) { }

/**
 * Connect to a TCP server
 * @param ip - ip address to which to connect
 * @param port - port on which to connect to IP
 * @returns bool if connection succeeded
 * @throws exception if unable to convert IP to binary format
 */
bool TcpClient::connect(char *ip, unsigned short port) 
	throw (const char *){
	
	// specify server IP and port
	struct sockaddr_in server_addr;

	// clear address structure
	memset(&server_addr, 0, sizeof(server_addr));
	
	server_addr.sin_family = family;
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

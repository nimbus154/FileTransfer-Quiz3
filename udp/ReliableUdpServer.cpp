#include <cstring>
#include <string>
#include "ReliableUdpServer.h"

ReliableUdpServer::ReliableUdpServer(unsigned short port, long address, int family) 
	throw (int) : UdpSocket(family) {
	
	sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	
	server_addr.sin_family = family;
   	server_addr.sin_addr.s_addr = htonl(address);
	server_addr.sin_port = htons(port);
	
	if(bind(sock_fd,(sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		throw errno;
	}
}	

/** * Wait to receive data from client * @param buffer - buffer in which to store data
 * @param buffer_length - size of the buffer
 * @returns number of bytes read, -1 on error
 */
int ReliableUdpServer::receive(void *buffer, int buffer_length) {

	sockaddr_in client_addr;
	socklen_t sockaddr_in_len = sizeof(client_addr);	
	
	// block until data received
	int received = recvfrom(sock_fd, buffer, buffer_length, 0, 
						   (sockaddr *)&client_addr, &sockaddr_in_len);
	if(received < 0) {
		return RECEIVE_ERROR;
	}
		
	// send response to client that we received x bytes
	std::string bytes_received = std::to_string(received);
	int sent = sendto(sock_fd, bytes_received.c_str(), bytes_received.size(), 
					 0, (sockaddr *)&client_addr, sockaddr_in_len);
	if(sent < 0) {
		return SEND_ERROR;
	}

	return received;
}	

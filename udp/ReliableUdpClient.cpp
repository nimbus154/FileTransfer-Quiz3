#include<cstring>
#include<errno.h>
#include<stdlib.h>
#include<iostream>
#include "ReliableUdpClient.h"
#define RECEIVE_BUFFER_LENGTH 20

ReliableUdpClient::ReliableUdpClient(char *ip, unsigned short port, int family) 
	throw (int) : UdpSocket(family) {
	
	// Initialize server data
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = family;
	server_addr.sin_port = htons(port);
		
	if(!inet_pton(family, ip, &server_addr.sin_addr.s_addr)) {
		std::cerr << "Inet__pton\n";
		throw errno;
	}

	server_addr_len = sizeof(server_addr);
}

/**
 * Send data and confirm its receipt with server
 * @returns true if send was successful, false if server did not receive packet
 * correctly
 */
bool ReliableUdpClient::send(const void *data, int length) 
	throw (int) {

	// send packet
	int sent = sendto(sock_fd, data, length, 0,
					(sockaddr *)&server_addr, server_addr_len);
	if(sent < 0) {
		std::cerr << "Send error\n";
		throw SEND_ERROR;
	}

	// wait for server to respond w/ number of bytes it received
	sockaddr_in server_response;
	socklen_t server_response_addr_len = sizeof(server_response);
	char receive_buffer[RECEIVE_BUFFER_LENGTH];
	int server_msg_size = recvfrom(sock_fd, 
								   receive_buffer, 
								   RECEIVE_BUFFER_LENGTH, 
								   0, 
								   (sockaddr *)&server_response, 
								   &server_response_addr_len);
	if(server_msg_size < 0) {
		std::cerr << "receive error\n";
		throw RECEIVE_ERROR;
	}
	receive_buffer[server_msg_size + 1] = '\0';
	int server_received = atoi(receive_buffer);

	// success if server/client received the same amount of data
	return server_received == sent;
}

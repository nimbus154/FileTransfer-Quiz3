#include "ReliableUdpClient.h"

ReliableUdpClient::ReliableUdpClient(char *ip, unsigned short port, int family) 
	throw (int) : UdpSocket(family) {
	
	// Initialize server data
	memset(&servaddr, 0, sizeof(servaddr));
	server_addr.sin_family = family;
	servaddr.sin_port = htons(port);
		
	if(!inet_pton(family, ip, &server_addr.sin_addr.s_addr)) {
		throw errno;
	}

	server_addr_len = sizeof(servaddr);
}

/**
 * Send data and confirm its receipt with server
 * @returns true if send was successful, false if server did not receive packet
 * correctly
 */
bool ReliableUdpClient::send(const void *data, int length) 
	throw (int) {

	// send packet, wait for response from server (ACK)
	// server should send back how many bytes it received
	// send number of bytes, followed by the data
	// server should respond with the number of bytes it received
	int sent = sendto(sock_fd, data, length, 0,
					(sockaddr *)&server_addr, server_addr_len);
	if(sent < 0) {
		throw SEND_ERROR;
	}

	// TODO define client/server in UdpSocket?
	// TODO remove all Client/Server functionality to socket class?
	int received = recvfrom(sock_fd, data, length, 0, 
							(sockaddr *)&client_addr, &sockaddr_in_len);
	if(received < 0) {
		throw RECEIVE_ERROR;
	}

	// TODO confirm that received the correct amount
	return received == sent;
}

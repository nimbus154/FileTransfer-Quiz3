#include "ReliableUdpClient.h"

ReliableUdpClient::ReliableUdpClient(char *ip, unsigned short port) {
	
	// TODO implement
}

bool ReliableUdpClient::send(const void *dadta, int length) {

	// TODO implement
	// send packet, wait for response from server (ACK)
	// server should send back how many bytes it received
	// send number of bytes, followed by the data
	// server should respond with the number of bytes it received
}

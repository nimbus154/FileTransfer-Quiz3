#ifndef RELIABLE_UDP_SERVER
#define RELIABLE_UDP_SERVER
#include "UdpSocket.h"
#include <arpa/inet.h>
class ReliableUdpServer:UdpSocket {
	public:
		ReliableUdpServer(unsigned short port, 
						  long address = INADDR_ANY, 
						  int family = AF_INET) 
			throw (int);

		int receive(void *buffer, int buffer_length);
};
#endif

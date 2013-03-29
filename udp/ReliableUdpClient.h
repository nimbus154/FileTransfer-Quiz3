#ifndef RELIABLE_UDP_CLIENT
#define RELIABLE_UDP_CLIENT
#include "UdpSocket.h"
#include <arpa/inet.h>
class ReliableUdpClient:UdpSocket {
	public:
		ReliableUdpClient(char *ip, unsigned short port, int family = AF_INET)
			throw (int);
		bool send(const void *data, int length);
};
#endif

#ifndef RELIABLE_UDP_CLIENT
#define RELIABLE_UDP_CLIENT
#include "UdpSocket.h"
#include <arpa/inet.h>
class ReliableUdpClient: public UdpSocket {
	public:
		ReliableUdpClient(char *ip, unsigned short port, int family = AF_INET)
			throw (int);
		bool send(const void *data, int length) throw (int);
	private:
		// details about server to which client will connect
		sockaddr_in server_addr;
		socklen_t server_addr_len;
};
#endif

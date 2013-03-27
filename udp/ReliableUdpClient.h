#ifndef RELIABLE_UDP_CLIENT
#define RELIABLE_UDP_CLIENT
class ReliableUdpClient {
	public:
		ReliableUdpClient(char *ip, unsigned short port);
		bool send(const void *data, int length);
};
#endif

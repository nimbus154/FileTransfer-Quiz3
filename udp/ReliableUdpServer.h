#ifndef RELIABLE_UDP_SERVER
#define RELIABLE_UDP_SERVER
class ReliableUdpServer {
	public:
		ReliableUdpServer(unsigned short port /*address to bind to?*/);
		int receive(void *buffer, int buffer_length);
};
#endif

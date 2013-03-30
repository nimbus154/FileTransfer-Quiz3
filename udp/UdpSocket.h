#ifndef UDP_SOCKET
#define UDP_SOCKET
#include <arpa/inet.h>
#define SEND_ERROR -2
#define RECEIVE_ERROR -1
class UdpSocket {
	public:
		UdpSocket(int family = AF_INET) throw (int);
	protected:
		int sock_fd;
		int family;
};
#endif

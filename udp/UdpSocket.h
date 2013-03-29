#ifndef UDP_SOCKET
#define UDP_SOCKET
#include <arpa/inet.h>
class UdpSocket {
	public:
		UdpSocket(int family = AF_INET) throw (int);
	protected:
		int sock_fd;
	private:
		int family;
};
#endif

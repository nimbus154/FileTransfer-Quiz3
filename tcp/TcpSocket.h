/**
 * A helper class for sockets
 */
#ifndef TCP_SOCKET_HELPER
#define TCP_SOCKET_HELPER
#include <arpa/inet.h>

class TcpSocket {

	public:
		TcpSocket(int family=AF_INET) throw (int);
		virtual int send(void *data, int size);
		virtual int receive(void *data, int size);

	protected:
		int sock_fd;
		int family;
};

#endif

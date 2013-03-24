/**
 * A helper class for sockets
 */
#ifndef TCP_SOCKET_HELPER
#define TCP_SOCKET_HELPER
#include <arpa/inet.h>

class TcpSocket {

	// an abstract superclass, defines everything but send methods
	public:
		TcpSocket(int domain=AF_INET) throw (int);
		bool connect(char *ip, unsigned short port) throw (const char *);
		int bind;	
		int listen;	
	private:
		int sock_fd;
		unsigned short port;
		char *ip;
		int domain;
};

#endif

/**
 * A TCP client
 */
#ifndef TCP_CLIENT
#define TCP_CLIENT
#include "TcpSocket.h"

class TcpClient : TcpSocket {

	public:
		TcpClient(int domain=AF_INET) throw (int);
		bool connect(char *ip, unsigned short port) throw (const char *);
};

#endif


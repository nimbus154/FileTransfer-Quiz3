/**
 * A TCP server
 */
#ifndef TCP_SERVER
#define TCP_SERVER
#include "TcpSocket.h"

class TcpServer : TcpSocket {

	public:
		TcpServer(int domain=AF_INET) throw (int);
		bool listen(unsigned short port, long address=INADDR_ANY);
		bool accept();
		int send(void *data, int size);
		int receive(void *data, int size);

	private:
		// fd of connected client
		int client_fd; 
};

#endif


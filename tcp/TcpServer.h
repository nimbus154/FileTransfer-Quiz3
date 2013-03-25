/**
 * A TCP server
 */
#ifndef TCP_SERVER
#define TCP_SERVER
#include "TcpSocket.h"

class TcpServer : public TcpSocket {

	public:
		TcpServer(int domain=AF_INET) throw (int);
		void listen(unsigned short port, long address=INADDR_ANY) throw (int);
		bool accept();
		int send(const void *data, int size);
		int receive(void *data, int size);
		void close() throw (int);

	private:
		// fd of connected client
		int client_fd; 
};

#endif


/* server.cpp
 * File transfer server, TCP
 * Chad Wyszynski
 * CPSC 471
 *
 * Usage:
 * ./server <LISTENING PORT>
 *
 * Example:
 * ./server 1234
 *
 * Listen for incoming connections on the specified port.
 *
 * When the client tries to connect, the server shall accept the connection.
 *
 * Use the connection created in part 2 to receive the name of the file from the
 * client.
 *
 * Create the file with the name received in step 3.
 *
 * Receive the file contents from the client and write the contents to the file
 * created in step 4.
 *
 * Close the connection and go back to waiting for more connections.
 */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

/**
 * Display directions for how to use the program
 */
void usage() {
	cout << "This is a simple TCP server for transferring files.\n"
		<< "To listen: \n\n"
		<< "\tserver <port>\n\n"
		<< "For example:\n"
		<< "\tserver 1234\n";
}

int main(int argc, char** argv) {
	if(argc != 2) {
		usage();
		return 0;
	}

	// Expect to receive size of object, then read that number of bytes
	struct sockaddr_in client_addr, server_addr;
	socklen_t client_len = sizeof(client_addr);


	// check for failure
	int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	// clear address structure
	memset(&server_addr, 0, sizeof(server_addr));
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(1234);

	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	// check for value >= 0
	bind(listen_fd, (sockaddr *) &server_addr, sizeof(server_addr));

	listen(listen_fd, 100); // should be >= 0, 100 pending clients

	// connection loop
	char buffer[10];
	while(true) {

		int connection = accept(listen_fd, 
								(sockaddr *)&client_addr, 
								&client_len);

		read(connection, buffer, 3);
		printf("%s\n", buffer);

		close(connection);
	}

	return 0;
}

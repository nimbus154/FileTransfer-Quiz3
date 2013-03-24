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
#include <stdlib.h>
#include <string>
#include <cstring>
#include <fstream>
#include "TcpServer.h"

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

	TcpServer server;
	
	// listen on user-supplied port
	// TODO handle bad parameters?
	server.listen(atoi(argv[1]));

	// connection loop
	char buffer[10];
	while(true) {

		if(server.accept()) {
			
			// process request
			// server_socket.write();
			// server_socket.read();
			/*
		read(connection, buffer, 4);
		cout << buffer << endl;

		close(connection);
		*/

		}

	}
	return 0;
}

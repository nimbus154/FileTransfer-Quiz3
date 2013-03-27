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

#define STREAM_SIZE 256

using namespace std;

void usage();
void accept_connections(TcpServer &server, char *buffer);
void fetch_data(char *data, TcpServer &server);
bool is_hangup(char *buffer);


int main(int argc, char** argv) {

	if(argc != 2) {
		usage();
		return 0;
	}
	
	// listen on user-supplied port
	// TODO handle bad parameters?
	TcpServer server;
	server.listen(atoi(argv[1]));

	char buffer[STREAM_SIZE];
	accept_connections(server, buffer);

	return 0;
}

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

/**
 * Connection loop
 */
void accept_connections(TcpServer &server, char *buffer) {
	// TODO deserialize integer and send values
	while(true) {
		if(server.accept()) {
			// clear old data
			memset(buffer, 0 , STREAM_SIZE);

			// by convention, first thing received is number of bytes
			// TODO receive filename, handle if file has same name in fdirectory
			fetch_data(buffer, server);
			cout << buffer << endl; // TODO create file

			// now, we receive the data
			while(!is_hangup(buffer)) {
				fetch_data(buffer, server);
				cout << buffer << endl;
			}
			cout << "Hangup received\n";
		}
	}
}

void fetch_data(char *buffer, TcpServer &server) {

	server.receive(buffer, sizeof(int));
	int bytes_to_receive = atoi(buffer);
	// TODO handle bytes longer than buffer

	server.receive(buffer, bytes_to_receive);
	buffer[bytes_to_receive] = '\0';
}

bool is_hangup(char *buffer) {

	return strcmp(buffer, "\0\0") == 0;
}

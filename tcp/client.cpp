/* client.cpp
 * File transfer client, TCP
 * Chad Wyszynski
 * CPSC 471
 *
 * General usage:
 * ./client <SERVER IP> <SERVER PORT> <FILE NAME>
 *
 * Example:
 * ./client 127.0.0.1 1234 file.txt
 *
 * Operations:
 * Establish a connection to the server.
 *
 * Send the name of the file to the server.
 *
 * Use the same connection to transfer the file contents to the server.
 *
 * Close the connection and exit.
 */
#include <sys/socket.h>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <arpa/inet.h>

using namespace std;

/**
 * Display directions for how to use the program
 */
void usage() {
	cout << "This is a simple TCP client for transferring files.\n"
		<< "To transfer files: \n\n"
		<< "\tclient <IP> <port> <file to transfer>\n\n"
		<< "For example:\n"
		<< "\tclient 127.0.0.1 1234 file.txt\n";
}

int main(int argc, char** argv) {

	if(argc != 4) {
		usage();
		return 0;
	}


	// TODO check all for failure

	// create a socket with socket()
	// check for non-negative
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	// specify server IP and port
	struct sockaddr_in server_addr;

	// clear address structure
	memset(&server_addr, 0, sizeof(server_addr));
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(1234);

	// set IP
	// check for > 0 return value
	inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

	// connect
	// returns -1 on error, 0 on success
	connect(sock_fd, (sockaddr*)&server_addr, sizeof(sockaddr));

	write(sock_fd, "yo\0", 3);
	
	// transfer size of object, then object
	// e.g. size of filename, then filename
	return 0;
}

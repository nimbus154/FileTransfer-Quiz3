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
#include <arpa/inet.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include "TcpClient.h"

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
	
	TcpClient client;
	string filename(argv[3]);
	// connect on IP and port
	if(client.connect(argv[1], atoi(argv[2]))) {

		cout << "Connected! Sending data..." << endl;
		client.send("yo!", 3);
	}
	else {
		cout << "Unable to connect -- is the IP and port correct?\n";
	}

	return 0;
}

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
#include <algorithm>
#include "TcpServer.h"

#define STREAM_SIZE 256
#define HANG_UP 2

using namespace std;

void usage();
void accept_connections(TcpServer &server, char *buffer);
int fetch_data(char *data, TcpServer &server);
bool create_file(char *filename, ofstream &file);
bool file_exists(string &filename);

int main(int argc, char** argv) {

	if(argc != 2) {
		usage();
		return 0;
	}
	
	// listen on user-supplied port
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

	while(true) {
		if(server.accept()) {
			// clear old data
			memset(buffer, 0 , STREAM_SIZE);

			// by convention, first thing received is number of bytes
			int bytes_read = fetch_data(buffer, server);
			ofstream output_file;
			create_file(buffer, output_file);

			// now, we receive the data
			int received_zero = 0;
			int total_received = bytes_read;

			while(received_zero < HANG_UP) {
				bytes_read = fetch_data(buffer, server);
				output_file.write(buffer, bytes_read);
				total_received += bytes_read;
				cout << "Received " << total_received << " bytes\n";

				if(bytes_read == 0) {
					received_zero++;
				}
			}

			cout << "Hangup received\n";
			output_file.close();
		}
	}
}

int fetch_data(char *buffer, TcpServer &server) {

	server.receive(buffer, sizeof(int));
	int bytes_to_receive = atoi(buffer);
	server.receive(buffer, bytes_to_receive);
	return bytes_to_receive;
}

bool create_file(char *filename, ofstream &file) {

	string original = string(filename);
	string new_file_name = string(filename);

	// find a unique filename
	int name_addition = 1;
	while(file_exists(new_file_name)) {

		new_file_name = original + to_string(name_addition);
		name_addition++;
	}

	file.open(new_file_name, ios::binary);
}

/**
 * Check if a file with a certain name already exists
 * @param filename - name of file to check
 * @return true if a file with that name already exists
 */
bool file_exists(string &filename) {
	// I stole this simple function from
	// http://www.cplusplus.com/forum/general/1796/
	ifstream file(filename);
	return file;
}

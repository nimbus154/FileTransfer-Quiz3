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
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include "ReliableUdpClient.h"

#define STREAM_SIZE 256
#define HANG_UP 2
#define RETRIES 5

using namespace std;

void usage();

void send_file(ifstream &file, string &filename, 
				char *ip, unsigned short port);

bool send_bytes(const void *data, int size, ReliableUdpClient &client);

void hangup(ReliableUdpClient &client);

bool send_or_timeout(const void *data, int length, ReliableUdpClient &client);

int main(int argc, char** argv) {

	if(argc != 4) {
		usage();
		return 0;
	}
	
	string filename(argv[3]);
	ifstream file(filename.c_str(), ios::binary);
	if(!file.is_open()) {
		cerr << "Unable to open input file\n";
		return 1;
	}

	send_file(file, filename, argv[1], atoi(argv[2]));
	file.close();
	return 0;
}

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

/**
 * Send file to server
 * @param file - file to send
 * @param filename - name of file to send
 * @param ip - IP address to which to send file
 * @param port - port to which to connect
 */
void send_file(ifstream &file, string &filename, 
				char *ip, unsigned short port) {

	ReliableUdpClient client(ip, port);
	cout << "Sending file..." << endl;

	int sent = 0;
	char data[STREAM_SIZE];

	filename.copy(data, STREAM_SIZE);
	data[filename.size()] = '\0';

	int chars_read = filename.size() + 1;

	if(!send_bytes(&data, chars_read, client)) {
		cerr << "Send failed\n";
		return;
	}
	sent+= chars_read;

	// read data from file
	while(file.good()) {
		file.read(data, STREAM_SIZE);
		chars_read = file.gcount();
		sent += chars_read;
		cout << "Sent " << sent << " bytes\n";

		if(!send_bytes(&data, chars_read, client)) {
			cerr << "Send failed\n";
			hangup(client);
			return;
		}
	}
	hangup(client);
}


/**
 * Sends data to server
 * @param data - data to send
 * @param length - number of bytes to send
 * @param client - reference to client to use to send data
 * @returns true if send succeeded
 */
bool send_bytes(const void *data, int length, ReliableUdpClient &client) {

	return send_or_timeout(to_string(length).c_str(), sizeof(length), client)
		&& send_or_timeout(data, length, client);
}

/**
 * Attempt to send data within a certain time
 */
bool send_or_timeout(const void *data, int length, ReliableUdpClient &client) {

	int tries = 0;
	while(!client.send(data, length) && tries++ < RETRIES);
	return tries < RETRIES; 
}

/**
 * Signal end of data and close connection
 */
void hangup(ReliableUdpClient &client) {

	// Make it repeat a whole bunch of times, to ensure it was received
	for(int i = 0; i < (HANG_UP * 5); i++) {
		send_or_timeout("\0", 1, client);
	}
}

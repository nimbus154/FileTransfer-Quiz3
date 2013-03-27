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
#include "TcpClient.h"

#define STREAM_SIZE 256

using namespace std;

void usage();

void send_file(ifstream &file, string &filename, 
				char *ip, unsigned short port);

bool send_bytes(void *data, int size, TcpClient &client);

void hangup(TcpClient &client);

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

	TcpClient client;
	if(client.connect(ip, port)) {
		cout << "Connected! Sending file..." << endl;

		// TODO send filename
		char data[STREAM_SIZE];
		int chars_read;

		// read data from file
		while(file.good()) {
			file.get(data, STREAM_SIZE);
			chars_read = file.gcount();

			if(!send_bytes(&data, chars_read, client)) {
				cerr << "Send failed!\n";
				return;
			}
			cout << chars_read << " bytes sent!\n";
		}
		hangup(client);
	}
	else {
		cout << "Unable to connect -- is the IP and port correct?\n";
	}
}


/**
 * Sends data to server
 * @param data - data to send
 * @param length - number of bytes to send
 * @param client - reference to client to use to send data
 * @returns true if send succeeded
 */
bool send_bytes(void *data, int length, TcpClient &client) {

	return client.send(to_string(length).c_str(), sizeof(length)) != -1
			&& client.send(data, length) != -1;
}

/**
 * Signal end of data and close connection
 */
void hangup(TcpClient &client) {

	cout << "Hanging up!\n";
}

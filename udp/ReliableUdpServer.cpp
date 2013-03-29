#include "ReliableUdpServer.h"

ReliableUdpServer::ReliableUdpServer(unsigned short port, long address, int family) 
	throw (int) : UdpSocket(family) {
	
	sockaddr_in servaddr, cliaddr;
	socklen_t sockaddr_in_len = 0;
		
	memset(&servaddr, 0, sizeof(servaddr));
	
	servaddr.sin_family = family;
   	servaddr.sin_addr.s_addr = htonl(address);
	servaddr.sin_port = htons(port);
	
	if(bind(sock_fd,(sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		throw errno;
	}
}	

int ReliableUdpServer::receive(void *buffer, int buffer_length) {

	// TODO implement
	// block until data received
	// send response to client that we received x bytes
	// return number of bytes received
	/* Get the size of the client address data structure */
	sockaddr_in_len = sizeof(cliaddr);	
	
	/* Get something from the client; Will block until the client
	 * sends. 
	 */
	if((numRecv = recvfrom(socketfd, recvBuff, MAX_RECV_SIZE, 0, 
		(sockaddr *)&cliaddr, &sockaddr_in_len)) < 0)
	{
		perror("recvfrom");
		exit(-1);
	}
	
	fprintf(stdout, "Received string: '%s' from the client\n", recvBuff);
	fflush(stdout);
	
		
	/* Retrieve the time */
	numSent = snprintf(sendBuff, MAX_SEND_SIZE, "%lu", (unsigned long)time(NULL));
	
	/* Send the time to the client */
	if((numSent = sendto(socketfd, sendBuff, numSent, 0,
		(sockaddr *)&cliaddr,sizeof(cliaddr))) < 0)
	{
		perror("sendto");
		exit(-1);
	}
}
}	

#include "UdpSocket.h"
#include <sys/socket.h>
#include <errno.h>
#define SEND_ERROR -2
#define RECEIVE_ERROR -1

UdpSocket::UdpSocket(int family) 
	throw (int) : family(family) {

	if((sock_fd = socket(family, SOCK_DGRAM, 0)) < 0) {
		throw errno;
	}
}

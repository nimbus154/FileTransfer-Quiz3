#include "UdpSocket.h"
#include <sys/socket.h>
#include <errno.h>

UdpSocket::UdpSocket(int family) 
	throw (int) : family(family) {

	if((sock_fd = socket(family, SOCK_DGRAM, 0)) < 0) {
		throw errno;
	}
}

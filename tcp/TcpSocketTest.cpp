#include <cassert>
#include "TcpSocket.h"

/**
 * Test ability to handle malformed IPs
 */
void testBadFormat() {

	bool threwError = false;

	TcpSocket tcp_sock;

	try {
		tcp_sock.connect("dog", 1234);
	}
	catch(const char *) {
		threwError = true;
	}

	assert(threwError); // handling bad urls
}

int main() {

	testBadFormat();
}

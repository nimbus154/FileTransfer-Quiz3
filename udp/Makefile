all: client server

client: client.cpp client.o socket.o
	g++ -std=c++0x -o client client.cpp client.o socket.o

server: server.cpp server.o socket.o
	g++ -std=c++0x -o server server.cpp server.o socket.o

client.o: ReliableUdpClient.h ReliableUdpClient.cpp socket.o
	g++ -std=c++0x -o client.o -c ReliableUdpClient.cpp socket.o

server.o: ReliableUdpServer.h ReliableUdpServer.cpp socket.o
	g++ -std=c++0x -o server.o -c ReliableUdpServer.cpp

socket.o: UdpSocket.h UdpSocket.cpp
	g++ -std=c++0x -o socket.o -c UdpSocket.cpp

clean:
	rm -rf server client test *.o

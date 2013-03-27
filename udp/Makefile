all: client server

client: client.cpp client.o
	g++ -std=c++0x -o client client.cpp client.o

server: server.cpp server.o
	g++ -std=c++0x -o server server.cpp server.o

client.o: ReliableUdpClient.h ReliableUdpClient.cpp
	g++ -std=c++0x -o client.o -c ReliableUdpClient.cpp

server.o: ReliableUdpServer.h ReliableUdpServer.cpp
	g++ -std=c++0x -o server.o -c ReliableUdpServer.cpp

clean:
	rm -rf server client test *.o

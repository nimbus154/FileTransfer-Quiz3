all: client server

client: client.cpp tcp.o
	g++ -o client client.cpp TcpSocket.o

server: server.cpp tcp.o
	g++ -o server server.cpp TcpSocket.o

tcp.o: TcpSocket.cpp TcpSocket.h
	g++ -o TcpSocket.o -c TcpSocket.cpp

test: TcpSocketTest.cpp tcp.o
	g++ -o test TcpSocketTest.cpp TcpSocket.o

clean:
	rm -rf server client test *.o

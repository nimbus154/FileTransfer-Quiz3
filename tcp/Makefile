all: client server

client: client.cpp tcp_client.o
	g++ -std=c++0x -o client client.cpp tcp_client.o tcp_socket.o

server: server.cpp tcp_server.o
	g++ -std=c++0x -o server server.cpp tcp_server.o tcp_socket.o

tcp_client.o: TcpClient.h TcpClient.cpp tcp_socket.o
	g++ -std=c++0x -o tcp_client.o -c TcpClient.cpp

tcp_server.o: TcpServer.h TcpServer.cpp tcp_socket.o
	g++ -std=c++0x -o tcp_server.o -c TcpServer.cpp

tcp_socket.o: TcpSocket.cpp TcpSocket.h
	g++ -std=c++0x -o tcp_socket.o -c TcpSocket.cpp

test: TcpSocketTest.cpp tcp.o
	g++ -std=c++0x -o test TcpSocketTest.cpp TcpSocket.o

clean:
	rm -rf server client test *.o

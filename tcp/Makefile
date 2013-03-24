all: client server

client: client.cpp tcp_client.o
	g++ -o client client.cpp tcp_client.o tcp_socket.o

server: server.cpp tcp_server.o
	g++ -o server server.cpp tcp_server.o tcp_socket.o

tcp_client.o: TcpClient.h TcpClient.cpp tcp_socket.o
	g++ -o tcp_client.o -c TcpClient.cpp

tcp_server.o: TcpServer.h TcpServer.cpp tcp_socket.o
	g++ -o tcp_server.o -c TcpServer.cpp

tcp_socket.o: TcpSocket.cpp TcpSocket.h
	g++ -o tcp_socket.o -c TcpSocket.cpp

test: TcpSocketTest.cpp tcp.o
	g++ -o test TcpSocketTest.cpp TcpSocket.o

clean:
	rm -rf server client test *.o

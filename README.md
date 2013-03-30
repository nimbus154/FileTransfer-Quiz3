# FileTransfer-Quiz3

File transfer using TCP and UDP. Quiz/homework assignment for CPSC 471: Networking.

## Notes

### General
To test transferring text files, use "keats.txt". To test transferring binary
files, I used the client ("./client 127.0.0.1 1234 client").

### UDP Implementation Notes
The server does not handle the following cases:
* Multiple connections
* Packets received in wrong order

## Assignment Directions

### Motivation
In this exercise you will develop a simple network application, in which the
client transfers a locally stored file to the server. This will give you
hands-on experience with TCP socket programming and will help you prepare for
the midterm and assignment 2.

#### The client

The client program shall be invoked using the following command line:
```bash
./client <SERVER IP> <SERVER PORT> <FILE NAME>
```

Where <SERVER IP> is the IP address of the server, <SERVER PORT> is the port on
which the server is listening, and <FILE NAME> is the name of a locally stored
file to be transfered to the server.

For example: 
```bash 
./client 127.0.0.1 1234 file.txt
```

When invoked, the client shall do the following:

1. Establish a connection to the server.

2. Send the name of the file to the server.

3. Use the same connection to transfer the file contents to the server.

4. Close the connection and exit.

#### The Server

The server shall be invoked using the following command line:

```bash
./server <LISTENING PORT>
```

where the <LISTENING PORT> is the port on which the server should listen for
incoming connections.

For example, 
```bash
./server 1234
```

When invoked, the server shall do the following:

1. Listen for incoming connections on the specified port.

2. When the client tries to connect, the server shall accept the connection.

3. Use the connection created in part 2 to receive the name of the file from the
   client.

4. Create the file with the name received in step 3.

5. Receive the file contents from the client and write the contents to the file
   created in step 4.

6. Close the connection and go back to waiting for more connections.

#### Hints
Prior to transmitting the name of the file, you may want your client to, first,
transmit the size of the file name e.g. file name "HelloWorld" is of size 10.
The server will receive the size of the file name, 10, and then wait to receive
10 bytes.  Similar approach can be applied for transmitting file contents.

 

### Submission:
You may work in groups of 3.

Please upload your files in response to this question.

You may use C, C++, Java, or Python.

However, you are highly encouraged to use C/C++.

These languages will teach you the most about how sockets actually work.

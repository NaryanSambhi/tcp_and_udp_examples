//Naryan Sambhi
// 11/2/2023 

//Goal: 
//Write and create a client for TCP / IP 
//with the goal of connecting to our server .cpp in our VM 


//using 

//WSAStartup -> socket() -> connect() -> 

// send() -> recv() -> 

//closesocket() -> WSACleanup() 

#define _WINSOCK_DEPRECATED_NO_WARNINGS


#include <WinSock2.h>

#include <windows.h>


#include <windows.networking.sockets.h>
#include <iostream>
#include <fstream> 
#pragma comment(lib, "Ws2_32.lib")


using namespace std;

int main()
{

	cout << "Starting..." << endl;

//WSAStartup() 
//responsible for starting up and configuring winsock lib
//to start we must declare wsa object and provide addres 

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout << "ERROR: Failed to start WSA" << std::endl;
		return 0;
	}

//Socket
//need to create a socket that we can use to call to the server 
//in order to do this must know transport service 
//TCP in this case.. 

	SOCKET ClientSocket;
	ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ClientSocket == INVALID_SOCKET) {
		WSACleanup();
		cout << "ERROR: Failed to create ServerSocket" << std::endl;
		return 0;
	}

//Connect
//on server side we needed to bind for listening, on client side we 
//need to start the three way handshake connection 
//to do that we use the connect fuction 

	sockaddr_in SvrAddr;
	SvrAddr.sin_family = AF_INET;
	SvrAddr.sin_port = htons(27000);
	SvrAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //local host ip number

	if ((connect(ClientSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr))) == SOCKET_ERROR) {
		cout << "ERROR: Connection attempted failed" << std::endl;
		closesocket(ClientSocket);
		WSACleanup();
		return 0;
	}

	//important to make sure we connect before code fires the message (windows to linux)
	//Sleep(2000);

//send

	char message[] = "Hello World"; //char string of message

	if (send(ClientSocket, message, sizeof(message), 0) == SOCKET_ERROR) { //send client socket, essage, size, and check for error
		cout << "ERROR: couldnt send the message" << WSAGetLastError() << endl; //error message
	}


//cleanup and wsacleanup 

	// Close the client socket
	closesocket(ClientSocket);
	// Cleanup the Winsock library
	WSACleanup();


	cout << "Ending..." << endl;

}

//Naryan Sambhi
// 11/2/2023 

//Goal: 
//Write and create a client for UDP
//with the goal of connecting to our server .cpp in our VM 

#define _WINSOCK_DEPRECATED_NO_WARNINGS


#include <WinSock2.h>

#include <windows.h>


#include <windows.networking.sockets.h>
#include <iostream>
#include <fstream> 
#pragma comment(lib, "Ws2_32.lib")
#include <WS2tcpip.h>

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

    ClientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (ClientSocket == -1) {
        WSACleanup();
        cout << "ERROR: Failed to create ClientSocket" << std::endl;
        return 0;
    }

    //Send tp

    sockaddr_in SvrAddr;
    socklen_t SvrAddrLen = sizeof(SvrAddr);

    SvrAddr.sin_family = AF_INET; // address family type internet
    SvrAddr.sin_port = htons(27000); //port 

    SvrAddr.sin_addr.s_addr = inet_addr("127.0.0.1");


    char BuffOUT[] = "Hello World"; //char string of message


    int bytesSent = sendto(ClientSocket, BuffOUT, sizeof(BuffOUT), 0, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr));
    if (bytesSent == -1) {
        cout << "ERROR: failed to send data" << std::endl;
    }
    else {
        cout << "Data sent successfully" << std::endl;
    }


    char BuffIN[1000];

    //recv from and print
    int bytes = recvfrom(ClientSocket, BuffIN, sizeof(BuffIN), 0, (struct sockaddr*)&SvrAddr, &SvrAddrLen);
    if (bytes == -1) {
        cout << "ERROR: failed to receive data" << std::endl;

    }
    else {
        BuffIN[bytes-1] = '\0'; // null-terminate the buffer
        cout << BuffIN << std::endl; //print buffer (or in other words our message)
    }


    //cleanup

    // Close the client socket
    closesocket(ClientSocket);
    WSACleanup();

    cout << "Ending..." << endl;

}

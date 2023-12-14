//Naryan Sambhi LAB 4
// 11/25/2023 

//goal 
//write and create a server in a virtual machine using visual studio 
// will recieve from a client in UDP method


// Socket() -> bind() -> //we no longer need listen and accept in UDP-> 

//recv() (from client) -> send() (to client) -> 

//closesocket())

#define _WINSOCK_DEPRECATED_NO_WARNINGS


#include <WinSock2.h>

#include <windows.h>


#include <windows.networking.sockets.h>
#include <iostream>
#include <fstream> 
#pragma comment(lib, "Ws2_32.lib")
#include <WS2tcpip.h>


using namespace std;

int main(void) {


    //starting.. 
    std::cout << "starting..." << std::endl;




    //WSAStartup() 
    //responsible for starting up and configuring winsock lib
    //to start we must declare wsa object and provide addres 

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "ERROR: Failed to start WSA" << std::endl;
        return 0;
    }




    //Socket
    //socket is required to be created so that we can configure a listening socket 
    //in order to do this we need to know the transport layer service planned to use 
    //in thiscase TCP S


    SOCKET ServerSocket;

    ServerSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (ServerSocket == -1) {
        cout << "ERROR: Failed to create ServerSocket" << std::endl;
        return 0;
    }


    //Bind 
    //in order for data packets to reach your application the OS must know the valid ip address 
    //and port num. This info goes in the TCP and IP packet headers
    //We dont create the headers but we must provide critical information for them to be configured 
    //the following code will bind or register our server to accept connections from any IP and link to 
    //a preselected port num 

    sockaddr_in SvrAddr;
    SvrAddr.sin_family = AF_INET;
    SvrAddr.sin_addr.s_addr = INADDR_ANY;
    SvrAddr.sin_port = htons(27000);

    if (bind(ServerSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr)) == -1) {
        closesocket(ServerSocket);
        WSACleanup();
        cout << "ERROR: Failed to bind ServerSocket" << std::endl;
        return 0;
    }

    //send / recive data 
    //once connection is made we must send and receive data
    //this is simply done by calling the send and receive functions 


    //declare sockarr_in structre 
    sockaddr_in SrcAddr; //this stores the IP of the sender
    socklen_t SrcAddrLen = sizeof(SrcAddr); //this stores the length of the IN structure, this is required for 
    //recv from to correctly interpret address information
    //TLDR Source address and length

    char buffIN[1000]; //buffer that will recieve our message

    //char buffOUT [1000]; //buffer that will send data back
    char buffOUT[] = "Hello client from server";


    //recv from and print
    int bytes = recvfrom(ServerSocket, buffIN, sizeof(buffIN), 0, (struct sockaddr*)&SrcAddr, &SrcAddrLen);
    if (bytes == -1) {
        cout << "ERROR: failed to receive data" << std::endl;

    }
    else {
        buffIN[bytes-1] = '\0'; // null-terminate the buffer
        cout << buffIN << std::endl; //print buffer (or in other words our message)
    }

    //reply back to client with sendto 


    int bytesSent = sendto(ServerSocket, buffOUT, strlen(buffOUT), 0, (struct sockaddr*)&SrcAddr, SrcAddrLen);
    if (bytesSent == -1) {
        cout << "ERROR: failed to send data" << std::endl;
    }
    else {
        cout << "Data sent successfully" << std::endl;
    }


    //Cleanup - close the sockets 
    //important to close and cleanup communication within programs 
    //without close, handshake can not be complete
    //also unregisters the port number with os
    //leaving it open for somebody else or next run off app 
    closesocket(ServerSocket);
    WSACleanup();

    return 0;
}



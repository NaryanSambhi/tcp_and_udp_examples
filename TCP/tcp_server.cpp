//Naryan Sambhi TCP / IP LAB 
// 11/2/2023 

//goal 
//write and create a server in a virtual machine using visual studio 
// must follow the format for servers in TCP / IP 


// Socket() -> bind() -> listen() -> accept -> 

//recv() (from client) -> send() (to client) -> 

//closesocket())

#define _WINSOCK_DEPRECATED_NO_WARNINGS


#include <windows.networking.sockets.h>
#include <iostream>
#include <fstream>
#pragma comment(lib, "Ws2_32.lib")

//#include <arpa/inet.h>

using namespace std;

int main (void) {
    

//starting.. 
    std::cout << "starting..." <<std::endl;


 //WSA Startup()


    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "Error to start WSA" << endl;
    }





//Socket
//socket is required to be created so that we can configure a listening socket 
//in order to do this we need to know the transport layer service planned to use 
//in thiscase TCP S


    SOCKET ServerSocket;

    ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (ServerSocket == -1) {
        WSACleanup();
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

    if (bind(ServerSocket, (struct sockaddr *)&SvrAddr, sizeof(SvrAddr)) == -1) {
        closesocket(ServerSocket);
        WSACleanup();
        cout << "ERROR: Failed to bind ServerSocket" << std::endl;
        return 0;
    }


//Listen 
//required by tcp. Since tcp is connection oriented we must listen for an incoming connection 
//the sysn request to start the handshake 
//so we must configure our socket to listen for reqs 

    if (listen(ServerSocket, 1) == -1) {
        closesocket(ServerSocket);
        WSACleanup();
        cout << "ERROR: listen failed to configure ServerSocket" << std::endl;
        return 0;
    }

//Accept 
//another tcp only block part of handshake process. accept will complete process and provide 
//connection with a unique socket and port num. This is the return of our accept call 
//will then block waiting for interrupt stating that it has recieved packet


    SOCKET ConnectionSocket;

    ConnectionSocket = -1;
    if ((ConnectionSocket = accept(ServerSocket, NULL, NULL)) == -1) {
        closesocket(ServerSocket);
        WSACleanup;
        return 0;
    }

//send / recive data 
//once connection is made we must send and receive data
//this is simply done by calling the send and receive functions 


char buff [1000]; //buffer that will recieve our message
int bytes; //in order to see if error

bytes = recv(ConnectionSocket, buff, sizeof(buff), 0); //function and define

if (bytes == -1) {
    cout << "ERROR: failed to receive data" << std::endl;

}
else {
    cout << buff << std::endl; //print buffer (or in other words our message)
}



//Cleanup - close the sockets 
//important to close and cleanup communication within programs 
//without close, handshake can not be complete
//also unregisters the port number with os
//leaving it open for somebody else or next run off app 

//so important to do


closesocket(ConnectionSocket);

closesocket(ServerSocket);

WSACleanup();



}


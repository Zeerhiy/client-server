#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "WS2_32.lib")

using namespace std;

int main()
{
    WSADATA WSAData;
    SOCKET serverSock;
    SOCKADDR_IN addr;

    WSAStartup(MAKEWORD(2,0), &WSAData);
    serverSock = socket(AF_INET, SOCK_STREAM, 0);

    //addr.sin_addr.s_addr = inet_addr("192.168.0.8"); // replace the ip with your futur server ip address. If server AND client are running on the same computer, you can use the local ip 127.0.0.1
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5555);

    connect(serverSock, (SOCKADDR *)&addr, sizeof(addr));
    cout << "Connected to server!" << endl;

    char buffer[1024]={'h', 'e', 'l', 'l', 'o', '.'};
    send(serverSock, buffer, sizeof(buffer), 0);
    cout << "Message sent!" << endl;

    closesocket(serverSock);
    WSACleanup();
    cout << "Socket closed." << endl << endl;
}
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "WS2_32.lib")

int main()
{
    WSADATA WSAData;
    SOCKET serverSock;
    SOCKADDR_IN addr;

    WSAStartup(MAKEWORD(2,0), &WSAData);
    serverSock = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5555);

    connect(serverSock, (SOCKADDR *)&addr, sizeof(addr));
    std::cout << "Connected to server!" << std::endl;
    std::string text;
    text.reserve(1024);
    std::cout << "Type text (q for quit)\n:>";
    std::cin >> text;
    while (text != "q") {
        send(serverSock, text.c_str(), text.size(), 0);
        std::cout << "Message sent!" << std::endl;
        recv(serverSock, const_cast<char*>(text.c_str()), text.size(), 0);
        std::cout << "Server says: " << text << "\n:>";
        std::cin >> text;
    }
    closesocket(serverSock);
    WSACleanup();
    std::cout << "Socket closed." << std::endl << std::endl;
}

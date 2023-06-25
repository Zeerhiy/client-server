#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "WS2_32.lib")


int main()
{
	WSADATA WSAData;

	SOCKET serverSock, clientSock;

	SOCKADDR_IN serverAddr, clientAddr;

	WSAStartup(MAKEWORD(2, 0), &WSAData);
	serverSock = socket(AF_INET, SOCK_STREAM, 0);

	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(5555);

	bind(serverSock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	listen(serverSock, 0);


	std::cout << "Listening for incoming connections..." << std::endl;

	char buffer[1024];
	int clientAddrSize = sizeof(clientAddr);
	if ((clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &clientAddrSize)) == INVALID_SOCKET)
	{
		closesocket(clientSock);
		WSACleanup();
		closesocket(serverSock);
		std::cout << "Invalid Socket." << std::endl;
	}
	std::cout << "Client connected!" << std::endl;
	std::string text;
	text.reserve(1024);
	while (1) {
		recv(clientSock, const_cast<char*>(text.c_str()), text.size(), 0);
		std::cout << "Client says: " << text << "\n:>";
		std::cin >> text;
		send(clientSock, text.c_str(), text.size(), 0);
	}

	closesocket(clientSock);
	std::cout << "Client disconnected." << std::endl;
	WSACleanup();
	closesocket(serverSock);
}

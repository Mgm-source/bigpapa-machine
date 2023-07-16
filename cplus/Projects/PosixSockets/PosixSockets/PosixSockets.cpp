// PosixSockets.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma comment(lib, "Ws2_32.lib")

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <WinSock2.h>

void printError(const std::string error)
{
	std::cerr << error << std::endl;
	exit(EXIT_FAILURE);
}

unsigned __stdcall newConnection(void* arglist)
{
	SOCKET client = reinterpret_cast<SOCKET>(arglist);

	int message_from_client_length = 0;
	char message_from_client[256u] = { };
	do
	{
		
		message_from_client_length = recv(client, message_from_client, sizeof(message_from_client), 0);

		if (message_from_client_length < 0)
		{
			break;
		}

		if (message_from_client_length > 0)
		{
			std::cout << client << " Message is " << message_from_client << std::endl;
			memset(message_from_client, 0, message_from_client_length);
		}

		if (message_from_client_length == 0)
		{
			break;
		}


	} while (client != INVALID_SOCKET);

	return closesocket(client);

}

int main(int argc, char** argv, char** envp)
{
	SOCKET server_socket_fd = {}, client_conn_fd = {};
	int client_addr_size = 0;
	struct sockaddr_in server_addr, client_addr;
	unsigned short port_number = 1132;;

	WSADATA wsaData;
    int iResult;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (server_socket_fd < 0)
	{
		printError("Erorr Opening Socket");
	}

	//clear socket address
	memset( &server_addr,0,sizeof(server_addr));
	server_addr.sin_family = AF_INET; 
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port_number);

	if(bind(server_socket_fd,(sockaddr*)&server_addr,sizeof(server_addr)) < 0)
	{
		std::cout << GetLastError();
		printError("Error binding");
	}

	//start listening
	listen(server_socket_fd, 3);

	client_addr_size = sizeof(client_addr);

	while (true)
	{
		//clear socket address
		memset(&client_addr, 0, sizeof(client_addr));

		client_conn_fd = accept(server_socket_fd, (sockaddr*)&client_addr, &client_addr_size);

		if (client_conn_fd < 0)
		{
			printError("Error accepting client");
		}

		_beginthreadex(nullptr, 0, newConnection, (void*)client_conn_fd, 0, 0);

	}

	closesocket(server_socket_fd);
	return 0;
}
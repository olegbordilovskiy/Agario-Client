#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int ConnectToServer() {
	WSADATA wsaData;
	WORD DLLVersion = MAKEWORD(2, 2);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		cerr << "Error" << endl;
		exit(1);
	};

	int sock = 0;
	struct sockaddr_in serv_addr;
	char buffer[2048] = { 0 };

	// создание сокета
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		cerr << "Failed to create socket\n";
		return -1;
	}

	// установка параметров сервера
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8888);

	// преобразование IP адреса из текстового в бинарный формат
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		cerr << "Invalid address\n";
		return -1;
	}

	// установка соединения с сервером
	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		cerr << "Failed to connect\n";
		return -1;
	}

	cout << "Connected to server\n";

	// бесконечный цикл для отправки и приема сообщений
	while (true) {
		// отправка случайного числа на сервер
		int numberToSend = rand() % 1000;
		char bufferSend[sizeof(int)];
		memcpy(bufferSend, &numberToSend, sizeof(numberToSend));
		send(sock, bufferSend, sizeof(bufferSend), 0);
		cout << "Sent: " << bufferSend << std::endl;
		printf("Sent: %d ", *(int*)bufferSend);

		// прием сообщения от сервера
		int valread = recv(sock, buffer, 2048, 0);

		int receivedInt = *(int*)buffer;
		cout << "Received: " << receivedInt << std::endl;

		Sleep(500);
	}

	return 0;
}

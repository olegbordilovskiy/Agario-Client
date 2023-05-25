#pragma once
#include "SFML/Network.hpp"
#include <iostream>

class Client
{
	sf::TcpSocket* socket;
	bool isConnected = false;
public:
	void ConnectToServer();
	void DisconnectFromServer();
	void SendPacketToServer(sf::Packet packet);
	bool IsClientConnected();
	sf::TcpSocket* GetClientSocket();
	sf::Packet GetServerPacket();
};


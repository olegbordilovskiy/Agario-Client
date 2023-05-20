#pragma once
#include "SFML/Network.hpp"
#include <iostream>

class Client
{
	sf::TcpSocket* socket = new sf::TcpSocket;
public:
	void ConnectToServer();
	sf::Packet GetMessageTest();
	void SendPlayerCondition(sf::Packet packet);
	sf::Packet GetServerPacket();
};


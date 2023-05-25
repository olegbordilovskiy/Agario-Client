#include "Client.h"

void Client::ConnectToServer()
{
	//std::string ipAddressString = "192.168.111.70";
	//sf::IpAddress serverIp("192.168.111.70");
	sf::IpAddress serverIp = sf::IpAddress::getLocalAddress();
	sf::TcpSocket* socketTemp = new sf::TcpSocket;
	socket = socketTemp;

	sf::Socket::Status status = sf::Socket::Error;

	unsigned short serverPort = 8888; // ���� �������

	while (status != sf::Socket::Done) {

		status = socket->connect(serverIp, serverPort);
		if (status != sf::Socket::Done)
		{
			std::cout << "������ ����������� � �������." << std::endl;
			isConnected = false;
		}
		else
		{
			std::cout << "����������� � ������� �������." << std::endl;
			isConnected = true;
		}
	}
}

void Client::DisconnectFromServer()
{
	socket->disconnect();
	delete socket;
}

sf::TcpSocket* Client::GetClientSocket()
{
	return socket;
}

void Client::SendPacketToServer(sf::Packet packet)
{
	socket->send(packet);
}

bool Client::IsClientConnected()
{
	return isConnected;
}

sf::Packet Client::GetServerPacket()
{
	sf::Packet packet;
	sf::Socket::Status status = socket->receive(packet);
	if (status == sf::Socket::Done)
		return packet;
}


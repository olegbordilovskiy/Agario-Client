#include "Client.h"

void Client::ConnectToServer()
{
    sf::IpAddress serverIP = sf::IpAddress::LocalHost; // IP-����� ������� (��������� ����)
    unsigned short serverPort = 8888; // ���� �������
    sf::Socket::Status status = socket->connect(serverIP, serverPort);
    if (status != sf::Socket::Done)
    {
        // ��������� ������ �����������
        std::cout << "������ ����������� � �������." << std::endl;
    }
    else
    {
        // �������� ����������� � �������
        std::cout << "����������� � ������� �������." << std::endl;
    }
}

void Client::SendPlayerCondition(sf::Packet packet)
{
    socket->send(packet);
}

sf::Packet Client::GetServerPacket()
{
    sf::Packet packet;
    sf::Socket::Status status = socket->receive(packet);
    if (status == sf::Socket::Done)
    {
        return packet;
    }
}

sf::Packet Client::GetMessageTest()
{
    sf::Packet packet;
    sf::Socket::Status status = socket->receive(packet);
    if (status == sf::Socket::Done)
    {
        return packet;
    }
}

#include "Client.h"

void Client::ConnectToServer()
{
    sf::IpAddress serverIP = sf::IpAddress::LocalHost; // IP-адрес сервера (локальный хост)
    unsigned short serverPort = 8888; // Порт сервера
    sf::Socket::Status status = socket->connect(serverIP, serverPort);
    if (status != sf::Socket::Done)
    {
        // Обработка ошибки подключения
        std::cout << "Ошибка подключения к серверу." << std::endl;
    }
    else
    {
        // Успешное подключение к серверу
        std::cout << "Подключение к серверу успешно." << std::endl;
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

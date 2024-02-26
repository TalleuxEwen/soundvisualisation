//
// Created by talleux on 2/23/24.
//

#include "Network.hpp"

Network::Network()
{
    if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cerr << "Socket creation error" << std::endl;
        exit(EXIT_FAILURE);
    }

    _server.sin_family = AF_INET;
    _server.sin_port = htons(6969);

    _connected = false;

    if (inet_pton(AF_INET, "127.0.0.1", &_server.sin_addr) <= 0)
    {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (::connect(_socket, (struct sockaddr *)&_server, sizeof(_server)) < 0)
    {
        std::cerr << "Connection Failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    _connected = true;

    std::cout << "Connected to server" << std::endl;
}

void Network::send(const std::string &message) const
{
    if (!_connected)
    {
        std::cerr << "Not connected" << std::endl;
        return;
    }

    ::send(_socket, message.c_str(), message.size(), 0);
}

double *Network::receive() const
{
    if (!_connected)
    {
        std::cerr << "Not connected" << std::endl;
        return nullptr;
    }

    double *received = new double[2];
    size_t valread = ::read(_socket, received, sizeof(double) * 2);
    if (valread == 0)
    {
        exit(EXIT_SUCCESS);
    }
    return received;
}

void Network::disconnect() {
    if (_connected)
    {
        ::close(_socket);
        _connected = false;
    }
}

bool Network::isConnected() const {
    return _connected;
}

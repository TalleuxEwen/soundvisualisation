//
// Created by talleux on 2/23/24.
//

#pragma once

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

class Network
{
    public:
        Network();
        ~Network() = default;
        void send(const std::string &message) const;
        double *receive() const;
        void disconnect();
        bool isConnected() const;

    private:
        int _socket;
        std::string _ip;
        int _port;
        bool _connected;
        struct sockaddr_in _server;
};

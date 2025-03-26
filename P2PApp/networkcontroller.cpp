#include "networkcontroller.h"

NetworkController::NetworkController(QObject *parent)
    : QObject{parent}
{
    connect(&_socket, &QTcpSocket::connected, this, &NetworkController::connected);
    connect(&_socket, &QTcpSocket::disconnected, this, &NetworkController::disconnected);
    connect(&_socket, &QTcpSocket::stateChanged, this, &NetworkController::stateChanged);
    connect(&_socket, &QTcpSocket::errorOccurred, this, &NetworkController::errorOccurred);
}

void NetworkController::connectToNetwork(QString ip, int port)
{
    if (_socket.isOpen()) {
        if (ip == _ip && port == _port) {
            return;
        }
        _socket.close();
    }
    std::cout << "Connecting to " << ip.toStdString() << ":" << port << std::endl;
    _ip = ip;
    _port = port;
    _socket.connectToHost(_ip, _port);
    std::cout << "Connected" << std::endl;
}

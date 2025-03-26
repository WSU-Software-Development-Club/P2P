#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include <QObject>
#include <QTcpSocket>
#include <iostream>

class NetworkController : public QObject
{
    Q_OBJECT
public:
    explicit NetworkController(QObject *parent = nullptr);
    void connectToNetwork(QString ip, int port);

signals:
    void connected();
    void disconnected();
    void stateChanged(QAbstractSocket::SocketState);
    void errorOccurred(QAbstractSocket::SocketError);

private:
    QTcpSocket _socket;
    QString _ip;
    int _port;
};

#endif // NETWORKCONTROLLER_H

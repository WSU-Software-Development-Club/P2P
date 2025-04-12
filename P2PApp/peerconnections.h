#ifndef PEERCONNECTIONS_H
#define PEERCONNECTIONS_H
#include "qforeach.h"
#include <QTcpSocket>
#include <list>
#include <regex>
#include <stdexcept>

class PeerConnections
{
public:
    PeerConnections() { }

    void write(std::string data) {
        tcpConnections.remove_if([](const QTcpSocket& obj){ return obj.isOpen(); });

        auto first = tcpConnections.begin();
        auto end = tcpConnections.end();
        while(true) {
            first->write(data.data());
            if (first == end)
                break;
            first++;
        }
    }

    std::vector<std::string> readAll() {
        std::vector<std::string> retVec = std::vector<std::string>();
        auto first = tcpConnections.begin();
        auto end = tcpConnections.end();
        while(true) {
            retVec.push_back(first->readAll().toStdString());
            if (first == end)
                break;
            first++;
        }
        tcpConnections.remove_if([](const QTcpSocket& obj){ return obj.isOpen(); });
    }

    bool AddPeer(std::string ipPort){
        QString ip;
        int port;
        std::smatch matches;
        if (std::regex_search(ipPort, matches, ipParse)) {
            if (matches.size() == 2) {
                try {
                    ip = QString::fromStdString(matches[1].str());
                    port = std::stoi(matches[2].str());
                }
                catch(std::exception e) {
                    return false;
                }
            }
            else
                return false;
        }
        else
            return false;

        QTcpSocket newPeer = QTcpSocket();

        newPeer.bind();
        newPeer.connectToHost(ip, port);
        if (newPeer.isValid()) {
            tcpConnections.push_back(newPeer);
            return true;
        }
        return false;
    }

    long int PeerCount() {
        return this->tcpConnections.size();
    }

    std::string GetPeerIP() {
        tcpConnections.remove_if([](const QTcpSocket& obj){ return obj.isOpen(); });
        std::vector<std::string> retVec = std::vector<std::string>();
        auto first = tcpConnections.begin();
        auto end = tcpConnections.end();
        while(true) {
            retVec.push_back(first->peerName().toStdString());
            if (first == end)
                break;
            first++;
        }
    }

private:
    const std::regex ipParse = std::regex("(.*):([0-9]*)");
    std::list<QTcpSocket> tcpConnections;
};

#endif // PEERCONNECTIONS_H

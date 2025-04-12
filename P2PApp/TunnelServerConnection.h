#ifndef PeerServerCONNECTION_H
#define PeerServerCONNECTION_H
#include <QTcpSocket>
#include <chrono>
#include <sstream>
#include <list>
#include <mutex>
#include <vector>

using namespace std::chrono_literals;

#define DEFAULT_SERVER_IP "localhost"
#define DEFAULT_PORT 8080

class TunnelServerConnection {
public:
    TunnelServerConnection() {}

    void Connect(std::string IP = DEFAULT_SERVER_IP, int port = DEFAULT_PORT)
    {
        serverConnection.bind();
        serverConnection.connectToHost(QString::fromStdString(IP), port);
        while (true) {
            mut.lock();
            outPutVec.push_back(serverConnection.readLine().toStdString());
            mut.unlock();
        }
    }

    // if needs to be optomized stack allocate and return reference to object
    // currently a little slow to facilitate memory safety
    std::vector<std::string> GetConnections() {
        std::vector<std::string> returnvec = std::vector<std::string>();
        if(mut.try_lock_for(1ms)) {
            std::swap(outPutVec, returnvec);
            mut.unlock();
        }

        return returnvec;
    }
private:
    std::timed_mutex mut;
    std::vector<std::string> outPutVec;
    std::vector<QTcpSocket> connections;
    QTcpSocket serverConnection;
};

#endif // PeerServerCONNECTION_H

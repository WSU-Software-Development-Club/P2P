#ifndef PeerServerCONNECTION_H
#define PeerServerCONNECTION_H
#include <QTcpSocket>
#include <chrono>
#include <sstream>
#include <mutex>

#define DEFAULT_SERVER_IP "localhost"

class PeerServerConnection
{
public:
    PeerServerConnection()
    {
        socket.bind(1300);
    }

    // always run in a thread as this runs forever
    bool ConnectToServer(QString ipOfServer = DEFAULT_SERVER_IP)
    {
        socket.connectToHost(ipOfServer, 8080);
        int numRead = 0, numReadTotal = 0;
        char buffer[50];


        forever {
            stream_mutex.lock();
            numRead  = socket.read(buffer, 50);

            stream << buffer;

            numReadTotal += numRead;
            stream_mutex.unlock();
            while(socket.bytesAvailable() == 0)
            {
                this->sendData();
            }
        }
    }

    std::stringstream GetStream() {
        std::stringstream returnStream;
        if (stream_mutex.try_lock_for(std::chrono::milliseconds(1)))
        {
            if (stream.good())
                returnStream.swap(stream);
            stream_mutex.unlock();
        }
        return returnStream;
    }

    void CreateServer(std::string &serverName, std::string &serverPassword)
    {


        // Send to server

        this->serverSendStream << "ServerName: " << serverName << ", ServerPassword: " << serverPassword;

    }

protected:
    void sendData(){

    }

    std::stringstream serverSendStream;
    std::timed_mutex stream_mutex;
    std::stringstream stream;
    QTcpSocket socket;
};

#endif // PeerServerCONNECTION_H

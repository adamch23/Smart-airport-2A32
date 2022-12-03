#ifndef DUMESSENGERSERVER_H
#define DUMESSENGERSERVER_H
#include <QTcpServer>

namespace DuarteCorporation
{
class DuMessengerSocket;
class DuMessengerServer : public QTcpServer
{
public:
    DuMessengerServer(QObject * parent = nullptr);
    bool startServer(qint16 port);
protected:
    void incomingConnection(qintptr handle);
private:
    QList<DuMessengerSocket *>mSockets;
};
}
#endif // DUMESSENGERSERVER_H

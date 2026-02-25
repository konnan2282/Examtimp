#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QDebug>
#include "heapsorter.h"

class MyServer : public QTcpServer {
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = nullptr) : QTcpServer(parent) {}

protected:
    void incomingConnection(qintptr socketDescriptor) override {
        QTcpSocket *socket = new QTcpSocket;
        socket->setSocketDescriptor(socketDescriptor);
        connect(socket, &QTcpSocket::readyRead, socket, [socket]() {
            QByteArray data = socket->readAll();
            QString request = QString::fromUtf8(data).trimmed();
            qDebug() << "Client:" << request;

            QString response = HeapSorter::processRequest(request);

            socket->write(response.toUtf8());
            socket->flush();
        });
        connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    }
};

#endif // MYSERVER_H

#include <QCoreApplication>
#include "myserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MyServer server;
    if(server.listen(QHostAddress::Any, 33333)){
        qDebug() << "Server started on port 33333...";
    } else {
        qDebug() << "Server failed to start";
        return 1;
    }
    return a.exec();
}

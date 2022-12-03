#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "DuMessengerServer.h"
#include <QDebug>
#include "widget.h"
#include "connection.h"
using namespace DuarteCorporation;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
     DuMessengerServer Server;
     //Widget e;
    Connection c;
    bool test=c.createconnection();
     MainWindow w;
    if(Server.startServer(3333) && test)
    {
        a.setStyle("fusion");
        w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

        qDebug() <<"Server started ...";
return a.exec();
}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


 qDebug() <<"Error:" <<Server.errorString();
 return 1;
    //return a.exec();
}

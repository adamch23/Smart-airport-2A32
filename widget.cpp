#include "widget.h"
#include "dumessengerconnectiondialog.h"
#include "ui_widget.h"
#include <QTcpSocket>
#include <QTextStream>
namespace DuarteCorporation
{
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mSocket = new QTcpSocket(this);

    connect(mSocket , &QTcpSocket :: readyRead , [&]() {
        QTextStream T(mSocket);
        auto text = T.readAll();
        ui->textEdit->append(text);
    });
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_envoyer_chat_clicked()
{
  QTextStream T(mSocket);
  T << ui->surnom->text() << ": " << ui->message_chat->text();
  mSocket->flush();
  ui->message_chat->clear();
}

void Widget::on_connecter_chat_clicked()
{
  DuMessengerConnectionDialog D(this);
  if(D.exec() == QDialog :: Rejected)
     {
      return;
  }
  mSocket->connectToHost(D.nomHost(),D.port());

}
}

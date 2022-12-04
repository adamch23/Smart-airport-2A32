#ifndef ARDUINOEVENEMENT_H
#define ARDUINOEVENEMENT_H


#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Arduinoevent
{
public:
    Arduinoevent();
    int connect_arduino_event(); // permet de connecter le PC à Arduino
    int close_arduino_event(); // permet de femer la connexion
    int write_to_arduino_event( QByteArray ); // envoyer des données vers arduino
    QByteArray read_from_arduino_event();  //recevoir des données de la carte Arduino
    QSerialPort* getserial_event();   // accesseur
    QString getarduino_port_name_event();
private:
QSerialPort * serial;
static const quint16 arduino_uno_vendor_id=9025;
static const quint16 arduino_uno_producy_id=67;
QString arduino_port_name_event;
bool arduino_is_available;
QByteArray data;  // contenant les données lues à partir d'Arduino
};



#endif // ARDUINOEVENEMENT_H
